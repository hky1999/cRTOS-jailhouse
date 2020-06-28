/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Minimal configuration for demo inmates, 1 CPU, 1 MB RAM, 1 serial port
 *
 * Copyright (c) Siemens AG, 2013
 *
 * Authors:
 *  Jan Kiszka <jan.kiszka@siemens.com>
 *
 * This work is licensed under the terms of the GNU GPL, version 2.  See
 * the COPYING file in the top-level directory.
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[22];
	struct jailhouse_cache cache_regions[1];
	struct jailhouse_irqchip irqchips[2];
	struct jailhouse_pio pio_regions[11];
	struct jailhouse_pci_device pci_devices[8];
	struct jailhouse_pci_capability pci_caps[9];

} __attribute__((packed)) config = {
	.cell = {
		.signature = JAILHOUSE_CELL_DESC_SIGNATURE,
		.revision = JAILHOUSE_CONFIG_REVISION,
		.name = "nuttx",
    .flags = JAILHOUSE_CELL_PASSIVE_COMMREG,
		.cpu_set_size = sizeof(config.cpus),
		.num_memory_regions = ARRAY_SIZE(config.mem_regions),
		.num_cache_regions = ARRAY_SIZE(config.cache_regions),
		.num_irqchips = ARRAY_SIZE(config.irqchips),
		.num_pio_regions = ARRAY_SIZE(config.pio_regions),
		.num_pci_devices = ARRAY_SIZE(config.pci_devices),
    .num_pci_caps = ARRAY_SIZE(config.pci_caps),
	},

	.cpus = {
		0x8,
	},

	.mem_regions = {
		/* cRTOS Shadow memory */
		{
			.phys_start = 0x148000000,
			.virt_start = 0x148000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0x108000000,
			.virt_start = 0,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
        JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE |
        JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0x148001000,
			.virt_start = 0x148001000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0x148005000,
			.virt_start = 0x148005000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ| JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_ROOTSHARED,
		},
		/* communication region */ {
			.virt_start = 0x80000000,
			.size       = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
		/* MemRegion: fb100000-fb100fff : 0000:03:00.2 */
		{
			.phys_start = 0xfb100000,
			.virt_start = 0xfb100000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb500000-fb500fff : 0000:03:00.2 */
		{
			.phys_start = 0xfb500000,
			.virt_start = 0xfb500000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb501000-fb501fff : 0000:03:00.2 */
		{
			.phys_start = 0xfb501000,
			.virt_start = 0xfb501000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb502000-fb502fff : 0000:03:00.1 */
		{
			.phys_start = 0xfb502000,
			.virt_start = 0xfb502000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb503000-fb503fff : 0000:03:00.1 */
		{
			.phys_start = 0xfb503000,
			.virt_start = 0xfb503000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb504000-fb504fff : 0000:03:00.0 */
		{
			.phys_start = 0xfb504000,
			.virt_start = 0xfb504000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb505000-fb505fff : 0000:03:00.0 */
		{
			.phys_start = 0xfb505000,
			.virt_start = 0xfb505000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb600000-fb600fff : 0000:02:00.2 */
		{
			.phys_start = 0xfb600000,
			.virt_start = 0xfb600000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb601000-fb601fff : 0000:02:00.2 */
		{
			.phys_start = 0xfb601000,
			.virt_start = 0xfb601000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb602000-fb602fff : 0000:02:00.1 */
		{
			.phys_start = 0xfb602000,
			.virt_start = 0xfb602000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb603000-fb603fff : 0000:02:00.1 */
		{
			.phys_start = 0xfb603000,
			.virt_start = 0xfb603000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb604000-fb604fff : 0000:02:00.0 */
		{
			.phys_start = 0xfb604000,
			.virt_start = 0xfb604000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: fb605000-fb605fff : 0000:02:00.0 */
		{
			.phys_start = 0xfb605000,
			.virt_start = 0xfb605000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		JAILHOUSE_SHMEM_NET_REGIONS(0x148200000, 1),
	},

	.cache_regions = {
		{
			.start = 0,
			.size = 10,
			.type = JAILHOUSE_CACHE_L3,
		},
	},

	.irqchips = {
		/* IOAPIC */ {
			.address = 0xfec00000,
			.id = 0x1f0ff,
			.pin_bitmap = {
				0x000001 /* ACPI IRQ */
			},
		},
		/* IOAPIC 2, GSI base 24 */
		{
			.address = 0xfec01000,
			.id = 0x1002c,
			.pin_bitmap = {
				0x000000
			},
		},
	},

	.pio_regions = {
		/* Port I/O: 0020-0021 : pic1 */
    PIO_RANGE(0x20, 0x2),
		/* Port I/O: 00a0-00a1 : pic2 */
    PIO_RANGE(0xa0, 0x2),
		/* Port I/O: 03f8-03ff : serial */
		PIO_RANGE(0x3f8, 0x8),
		/* Port I/O: d000-d007 : 0000:03:00.2 */
		PIO_RANGE(0xd000, 0x8),
		/* Port I/O: d010-d017 : 0000:03:00.2 */
		PIO_RANGE(0xd010, 0x8),
		/* Port I/O: d020-d027 : 0000:03:00.1 */
		PIO_RANGE(0xd020, 0x8),
		/* Port I/O: d030-d037 : 0000:03:00.0 */
		PIO_RANGE(0xd030, 0x8),
		/* Port I/O: e000-e007 : 0000:02:00.2 */
		PIO_RANGE(0xe000, 0x8),
		/* Port I/O: e010-e017 : 0000:02:00.2 */
		PIO_RANGE(0xe010, 0x8),
		/* Port I/O: e020-e027 : 0000:02:00.1 */
		PIO_RANGE(0xe020, 0x8),
		/* Port I/O: e030-e037 : 0000:02:00.0 */
		PIO_RANGE(0xe030, 0x8),
	},
	.pci_devices = {
		{ /* IVSHMEM-NET */
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0x0000,
			.iommu = 1,
			.bdf = 0x0d << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_MSIX,
			.num_msix_vectors = 2,
			.shmem_regions_start = 18,
			.shmem_dev_id = 1,
			.shmem_peers = 2,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
		},
		{ /* Shadow */
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0x0000,
			.iommu = 1,
			.bdf = 0x0e << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_MSIX,
			.num_msix_vectors = 16,
			.shmem_regions_start = 0,
			.shmem_dev_id = 1,
			.shmem_peers = 2,
			.shmem_protocol = 0x0002,
		},
		/* PCIDevice: 02:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x200,
			.bar_mask = {
				0xfffffff8, 0xfffff000, 0x00000000,
				0x00000000, 0x00000000, 0xfffff000,
			},
			.caps_start = 0,
			.num_caps = 5,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 02:00.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x201,
			.bar_mask = {
				0xfffffff8, 0xfffff000, 0x00000000,
				0x00000000, 0x00000000, 0xfffff000,
			},
			.caps_start = 5,
			.num_caps = 4,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 02:00.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x202,
			.bar_mask = {
				0xfffffff8, 0xfffffff8, 0xfffff000,
				0x00000000, 0x00000000, 0xfffff000,
			},
			.caps_start = 5,
			.num_caps = 4,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 03:00.0 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x300,
			.bar_mask = {
				0xfffffff8, 0xfffff000, 0x00000000,
				0x00000000, 0x00000000, 0xfffff000,
			},
			.caps_start = 0,
			.num_caps = 5,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 03:00.1 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x301,
			.bar_mask = {
				0xfffffff8, 0xfffff000, 0x00000000,
				0x00000000, 0x00000000, 0xfffff000,
			},
			.caps_start = 5,
			.num_caps = 4,
			.num_msi_vectors = 8,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
		/* PCIDevice: 03:00.2 */
		{
			.type = JAILHOUSE_PCI_TYPE_DEVICE,
			.iommu = 1,
			.domain = 0x0,
			.bdf = 0x302,
			.bar_mask = {
				0xfffffff8, 0xfffffff8, 0xfffff000,
				0x00000000, 0x00000000, 0xfffff000,
			},
			.caps_start = 5,
			.num_caps = 4,
			.num_msi_vectors = 1,
			.msi_64bits = 1,
			.msi_maskable = 0,
			.num_msix_vectors = 0,
			.msix_region_size = 0x0,
			.msix_address = 0x0,
		},
	},

	.pci_caps = {
		/* PCIDevice: 02:00.0 */
		/* PCIDevice: 03:00.0 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x78,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x80,
			.len = 0x14,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_VC | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x10,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x800,
			.len = 0x40,
			.flags = 0,
		},
		/* PCIDevice: 02:00.1 */
		/* PCIDevice: 02:00.2 */
		/* PCIDevice: 03:00.1 */
		/* PCIDevice: 03:00.2 */
		{
			.id = PCI_CAP_ID_MSI,
			.start = 0x50,
			.len = 0xe,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_PM,
			.start = 0x78,
			.len = 0x8,
			.flags = JAILHOUSE_PCICAPS_WRITE,
		},
		{
			.id = PCI_CAP_ID_EXP,
			.start = 0x80,
			.len = 0x14,
			.flags = 0,
		},
		{
			.id = PCI_EXT_CAP_ID_ERR | JAILHOUSE_PCI_EXT_CAP,
			.start = 0x100,
			.len = 0x40,
			.flags = 0,
		},
    },
};
