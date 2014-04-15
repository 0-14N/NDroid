/*
 *  Dynamic device configuration and creation.
 *
 *  Copyright (c) 2009 CodeSourcery
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston MA  02110-1301 USA
 */

/* The theory here is that it should be possible to create a machine without
   knowledge of specific devices.  Historically board init routines have
   passed a bunch of arguments to each device, requiring the board know
   exactly which device it is dealing with.  This file provides an abstract
   API for device configuration and initialization.  Devices will generally
   inherit from a particular bus (e.g. PCI or I2C) rather than
   this API directly.  */

#include "net.h"
#include "qdev.h"
#include "sysemu.h"
#include "monitor.h"
#include "blockdev.h"

struct DeviceProperty {
    const char *name;
    DevicePropType type;
    union {
        uint64_t i;
        void *ptr;
    } value;
    DeviceProperty *next;
};

struct DeviceType {
    DeviceInfo *info;
    DeviceType *next;
};

/* This is a nasty hack to allow passing a NULL bus to qdev_create.  */
static BusState *main_system_bus;

static DeviceType *device_type_list;

/* Register a new device type.  */
void qdev_register(DeviceInfo *info)
{
    DeviceType *t;

    assert(info->size >= sizeof(DeviceState));

    t = qemu_mallocz(sizeof(DeviceType));
    t->next = device_type_list;
    device_type_list = t;
    t->info = info;
}

/* Create a new device.  This only initializes the device state structure
   and allows properties to be set.  qdev_init should be called to
   initialize the actual device emulation.  */
DeviceState *qdev_create(BusState *bus, const char *name)
{
    DeviceType *t;
    DeviceState *dev;

    for (t = device_type_list; t; t = t->next) {
        if (strcmp(t->info->name, name) == 0) {
            break;
        }
    }
    if (!t) {
        hw_error("Unknown device '%s'\n", name);
    }

    dev = qemu_mallocz(t->info->size);
    dev->type = t;

    if (!bus) {
        /* ???: This assumes system busses have no additional state.  */
        if (!main_system_bus) {
            main_system_bus = qbus_create(BUS_TYPE_SYSTEM, sizeof(BusState),
                                          NULL, "main-system-bus");
        }
        bus = main_system_bus;
    }
    if (t->info->bus_type != bus->type) {
        /* TODO: Print bus type names.  */
        hw_error("Device '%s' on wrong bus type (%d/%d)", name,
                 t->info->bus_type, bus->type);
    }
    dev->parent_bus = bus;
    QLIST_INSERT_HEAD(&bus->children, dev, sibling);
    return dev;
}

int qdev_device_help(QemuOpts *opts)
{
#ifdef CONFIG_ANDROID  /* Not ready yet, will remove when we properly integrate upstream qdev */
    return 0;
#else
    const char *driver;
    DeviceInfo *info;
    Property *prop;

    driver = qemu_opt_get(opts, "driver");
    if (driver && !strcmp(driver, "?")) {
        for (info = device_info_list; info != NULL; info = info->next) {
            if (info->no_user) {
                continue;       /* not available, don't show */
            }
            qdev_print_devinfo(info);
        }
        return 1;
    }

    if (!qemu_opt_get(opts, "?")) {
        return 0;
    }

    info = qdev_find_info(NULL, driver);
    if (!info) {
        return 0;
    }

    for (prop = info->props; prop && prop->name; prop++) {
        /*
         * TODO Properties without a parser are just for dirty hacks.
         * qdev_prop_ptr is the only such PropertyInfo.  It's marked
         * for removal.  This conditional should be removed along with
         * it.
         */
        if (!prop->info->parse) {
            continue;           /* no way to set it, don't show */
        }
        error_printf("%s.%s=%s\n", info->name, prop->name, prop->info->name);
    }
    return 1;
#endif
}

DeviceState *qdev_device_add(QemuOpts *opts)
{
#ifdef CONFIG_ANDROID  /* Not ready yet */
    return NULL;
#else
    const char *driver, *path, *id;
    DeviceInfo *info;
    DeviceState *qdev;
    BusState *bus;

    driver = qemu_opt_get(opts, "driver");
    if (!driver) {
        qerror_report(QERR_MISSING_PARAMETER, "driver");
        return NULL;
    }

    /* find driver */
    info = qdev_find_info(NULL, driver);
    if (!info || info->no_user) {
        qerror_report(QERR_INVALID_PARAMETER_VALUE, "driver", "a driver name");
        error_printf_unless_qmp("Try with argument '?' for a list.\n");
        return NULL;
    }

    /* find bus */
    path = qemu_opt_get(opts, "bus");
    if (path != NULL) {
        bus = qbus_find(path);
        if (!bus) {
            return NULL;
        }
        if (bus->info != info->bus_info) {
            qerror_report(QERR_BAD_BUS_FOR_DEVICE,
                           driver, bus->info->name);
            return NULL;
        }
    } else {
        bus = qbus_find_recursive(main_system_bus, NULL, info->bus_info);
        if (!bus) {
            qerror_report(QERR_NO_BUS_FOR_DEVICE,
                           info->name, info->bus_info->name);
            return NULL;
        }
    }
    if (qdev_hotplug && !bus->allow_hotplug) {
        qerror_report(QERR_BUS_NO_HOTPLUG, bus->name);
        return NULL;
    }

    /* create device, set properties */
    qdev = qdev_create_from_info(bus, info);
    id = qemu_opts_id(opts);
    if (id) {
        qdev->id = id;
    }
    if (qemu_opt_foreach(opts, set_property, qdev, 1) != 0) {
        qdev_free(qdev);
        return NULL;
    }
    if (qdev_init(qdev) < 0) {
        qerror_report(QERR_DEVICE_INIT_FAILED, driver);
        return NULL;
    }
    qdev->opts = opts;
    return qdev;
#endif
}

/* Initialize a device.  Device properties should be set before calling
   this function.  IRQs and MMIO regions should be connected/mapped after
   calling this function.  */
void qdev_init(DeviceState *dev)
{
    dev->type->info->init(dev, dev->type->info);
}

/* Unlink device from bus and free the structure.  */
void qdev_free(DeviceState *dev)
{
    QLIST_REMOVE(dev, sibling);
    qemu_free(dev);
}

static DeviceProperty *create_prop(DeviceState *dev, const char *name,
                                   DevicePropType type)
{
    DeviceProperty *prop;

    /* TODO: Check for duplicate properties.  */
    prop = qemu_mallocz(sizeof(*prop));
    prop->name = qemu_strdup(name);
    prop->type = type;
    prop->next = dev->props;
    dev->props = prop;

    return prop;
}

void qdev_set_prop_int(DeviceState *dev, const char *name, uint64_t value)
{
    DeviceProperty *prop;

    prop = create_prop(dev, name, PROP_TYPE_INT);
    prop->value.i = value;
}

void qdev_set_prop_dev(DeviceState *dev, const char *name, DeviceState *value)
{
    DeviceProperty *prop;

    prop = create_prop(dev, name, PROP_TYPE_DEV);
    prop->value.ptr = value;
}

void qdev_set_prop_ptr(DeviceState *dev, const char *name, void *value)
{
    DeviceProperty *prop;

    prop = create_prop(dev, name, PROP_TYPE_PTR);
    prop->value.ptr = value;
}

void qdev_set_netdev(DeviceState *dev, NICInfo *nd)
{
    assert(!dev->nd);
    dev->nd = nd;
}


/* Get a character (serial) device interface.  */
CharDriverState *qdev_init_chardev(DeviceState *dev)
{
    static int next_serial;
    static int next_virtconsole;
    /* FIXME: This is a nasty hack that needs to go away.  */
    if (strncmp(dev->type->info->name, "virtio", 6) == 0) {
        return virtcon_hds[next_virtconsole++];
    } else {
        return serial_hds[next_serial++];
    }
}

BusState *qdev_get_parent_bus(DeviceState *dev)
{
    return dev->parent_bus;
}

static DeviceProperty *find_prop(DeviceState *dev, const char *name,
                                 DevicePropType type)
{
    DeviceProperty *prop;

    for (prop = dev->props; prop; prop = prop->next) {
        if (strcmp(prop->name, name) == 0) {
            assert (prop->type == type);
            return prop;
        }
    }
    return NULL;
}

uint64_t qdev_get_prop_int(DeviceState *dev, const char *name, uint64_t def)
{
    DeviceProperty *prop;

    prop = find_prop(dev, name, PROP_TYPE_INT);
    if (!prop) {
        return def;
    }

    return prop->value.i;
}

void *qdev_get_prop_ptr(DeviceState *dev, const char *name)
{
    DeviceProperty *prop;

    prop = find_prop(dev, name, PROP_TYPE_PTR);
    assert(prop);
    return prop->value.ptr;
}

DeviceState *qdev_get_prop_dev(DeviceState *dev, const char *name)
{
    DeviceProperty *prop;

    prop = find_prop(dev, name, PROP_TYPE_DEV);
    if (!prop) {
        return NULL;
    }
    return prop->value.ptr;
}

void qdev_init_gpio_in(DeviceState *dev, qemu_irq_handler handler, int n)
{
    assert(dev->num_gpio_in == 0);
    dev->num_gpio_in = n;
    dev->gpio_in = qemu_allocate_irqs(handler, dev, n);
}

void qdev_init_gpio_out(DeviceState *dev, qemu_irq *pins, int n)
{
    assert(dev->num_gpio_out == 0);
    dev->num_gpio_out = n;
    dev->gpio_out = pins;
}

qemu_irq qdev_get_gpio_in(DeviceState *dev, int n)
{
    assert(n >= 0 && n < dev->num_gpio_in);
    return dev->gpio_in[n];
}

void qdev_connect_gpio_out(DeviceState * dev, int n, qemu_irq pin)
{
    assert(n >= 0 && n < dev->num_gpio_out);
    dev->gpio_out[n] = pin;
}

VLANClientState *qdev_get_vlan_client(DeviceState *dev,
                                      NetCanReceive *can_receive,
                                      NetReceive *receive,
                                      NetReceiveIOV *receive_iov,
                                      NetCleanup *cleanup,
                                      void *opaque)
{
    NICInfo *nd = dev->nd;
    assert(nd);
    return qemu_new_vlan_client(nd->vlan, nd->model, nd->name, can_receive,
                                receive, receive_iov, cleanup, opaque);
}


void qdev_get_macaddr(DeviceState *dev, uint8_t *macaddr)
{
    memcpy(macaddr, dev->nd->macaddr, 6);
}

static int next_block_unit[IF_COUNT];

/* Get a block device.  This should only be used for single-drive devices
   (e.g. SD/Floppy/MTD).  Multi-disk devices (scsi/ide) should use the
   appropriate bus.  */
BlockDriverState *qdev_init_bdrv(DeviceState *dev, BlockInterfaceType type)
{
    int unit = next_block_unit[type]++;
    DriveInfo* info;

    info = drive_get(type, 0, unit);
    if (info == NULL) {
        return NULL;
    }
    return info->bdrv;
}

BusState *qdev_get_child_bus(DeviceState *dev, const char *name)
{
    BusState *bus;

    QLIST_FOREACH(bus, &dev->child_bus, sibling) {
        if (strcmp(name, bus->name) == 0) {
            return bus;
        }
    }
    return NULL;
}

static int next_scsi_bus;

/* Create a scsi bus, and attach devices to it.  */
/* TODO: Actually create a scsi bus for hotplug to use.  */
void scsi_bus_new(DeviceState *host, SCSIAttachFn attach)
{
   int bus = next_scsi_bus++;
   int unit;
   DriveInfo* info;

   for (unit = 0; unit < MAX_SCSI_DEVS; unit++) {
       info = drive_get(IF_SCSI, bus, unit);
       if (info == NULL) {
           continue;
       }
       attach(host, info->bdrv, unit);
   }
}

BusState *qbus_create(BusType type, size_t size,
                      DeviceState *parent, const char *name)
{
    BusState *bus;

    bus = qemu_mallocz(size);
    bus->type = type;
    bus->parent = parent;
    bus->name = qemu_strdup(name);
    QLIST_INIT(&bus->children);
    if (parent) {
        QLIST_INSERT_HEAD(&parent->child_bus, bus, sibling);
    }
    return bus;
}

static const char *bus_type_names[] = {
    [ BUS_TYPE_SYSTEM ] = "System",
    [ BUS_TYPE_PCI ]    = "PCI",
    [ BUS_TYPE_SCSI ]   = "SCSI",
    [ BUS_TYPE_I2C ]    = "I2C",
    [ BUS_TYPE_SSI ]    = "SSI",
};

#define qdev_printf(fmt, ...) monitor_printf(mon, "%*s" fmt, indent, "", ## __VA_ARGS__)
static void qbus_print(Monitor *mon, BusState *bus, int indent);

static void qdev_print(Monitor *mon, DeviceState *dev, int indent)
{
    DeviceProperty *prop;
    BusState *child;
    qdev_printf("dev: %s\n", dev->type->info->name);
    indent += 2;
    if (dev->num_gpio_in) {
        qdev_printf("gpio-in %d\n", dev->num_gpio_in);
    }
    if (dev->num_gpio_out) {
        qdev_printf("gpio-out %d\n", dev->num_gpio_out);
    }
    for (prop = dev->props; prop; prop = prop->next) {
        switch (prop->type) {
        case PROP_TYPE_INT:
            qdev_printf("prop-int %s 0x%" PRIx64 "\n", prop->name,
                        prop->value.i);
            break;
        case PROP_TYPE_PTR:
            qdev_printf("prop-ptr %s\n", prop->name);
            break;
        case PROP_TYPE_DEV:
            qdev_printf("prop-dev %s %s\n", prop->name,
                        ((DeviceState *)prop->value.ptr)->type->info->name);
            break;
        default:
            qdev_printf("prop-unknown%d %s\n", prop->type, prop->name);
            break;
        }
    }
    switch (dev->parent_bus->type) {
    case BUS_TYPE_SYSTEM:
        sysbus_dev_print(mon, dev, indent);
        break;
    default:
        break;
    }
    QLIST_FOREACH(child, &dev->child_bus, sibling) {
        qbus_print(mon, child, indent);
    }
}

static void qbus_print(Monitor *mon, BusState *bus, int indent)
{
    struct DeviceState *dev;

    qdev_printf("bus: %s\n", bus->name);
    indent += 2;
    qdev_printf("type %s\n", bus_type_names[bus->type]);
    QLIST_FOREACH(dev, &bus->children, sibling) {
        qdev_print(mon, dev, indent);
    }
}
#undef qdev_printf

void do_info_qtree(Monitor *mon)
{
    if (main_system_bus)
        qbus_print(mon, main_system_bus, 0);
}
