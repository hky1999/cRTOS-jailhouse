/*
 * Jailhouse, a Linux-based partitioning hypervisor
 *
 * Copyright (c) Siemens AG, 2014-2017
 *
 * Hand crafted configuration for Nuttx in cRTOS
 *
 * Copyright (c) ChungFan Yang @ Fixstars corporation, 2020
 *    <chungfan.yang@fixstars.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
 * THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <jailhouse/types.h>
#include <jailhouse/cell-config.h>

struct {
	struct jailhouse_cell_desc cell;
	__u64 cpus[1];
	struct jailhouse_memory mem_regions[14];
	struct jailhouse_cache cache_regions[0];
	struct jailhouse_irqchip irqchips[1];
	struct jailhouse_pio pio_regions[3];
	struct jailhouse_pci_device pci_devices[4];
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
		.console = {
			.type = JAILHOUSE_CON_TYPE_8250,
			.flags = JAILHOUSE_CON_ACCESS_PIO,
			.address = 0x3f8,
		},
	},

	.cpus = {
		0x8,
	},

	.mem_regions = {
		/* cRTOS Shadow memory */
		{
			.phys_start = 0x42000000,
			.virt_start = 0x42000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0x42001000,
			.virt_start = 0,
			.size = 0x40000000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_EXECUTE | JAILHOUSE_MEM_LOADABLE |
				JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0x82001000,
			.virt_start = 0x82001000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_ROOTSHARED,
		},
		{
			.phys_start = 0x82005000,
			.virt_start = 0x82005000,
			.size = 0x4000,
			.flags = JAILHOUSE_MEM_READ| JAILHOUSE_MEM_WRITE | JAILHOUSE_MEM_ROOTSHARED,
		},
			/* communication region */ {
			.virt_start = 0x82010000,
			.size       = 0x00001000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE |
				JAILHOUSE_MEM_COMM_REGION,
		},
		JAILHOUSE_SHMEM_NET_REGIONS(0x82205000, 1),
		/* MemRegion: f0000000-f0000fff : do not know why*/
		{
			.phys_start = 0xf0000000,
			.virt_start = 0xf0000000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: f7c00000-f7c00fff : 0000:03:00.1 */
		{
			.phys_start = 0xf7c00000,
			.virt_start = 0xf7c00000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: f7c01000-f7c01fff : 0000:03:00.1 */
		{
			.phys_start = 0xf7c01000,
			.virt_start = 0xf7c01000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: f7c02000-f7c02fff : 0000:03:00.0 */
		{
			.phys_start = 0xf7c02000,
			.virt_start = 0xf7c02000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
		/* MemRegion: f7c03000-f7c03fff : 0000:03:00.0 */
		{
			.phys_start = 0xf7c03000,
			.virt_start = 0xf7c03000,
			.size = 0x1000,
			.flags = JAILHOUSE_MEM_READ | JAILHOUSE_MEM_WRITE,
		},
	},

	.cache_regions = {
	},

	.irqchips = {
		/* IOAPIC 8, GSI base 0 */
		{
			.address = 0xfec00000,
			.id = 0x1f0f8,
			.pin_bitmap = {
				0xffffffff, 0xffffffff, 0xffffffff, 0xffffffff
			},
		},
	},

	.pio_regions = {
		/* Port I/O: e000-e007 : 0000:03:00.1 */
		PIO_RANGE(0xe000, 0x8),
		/* Port I/O: e010-e017 : 0000:03:00.0 */
		PIO_RANGE(0xe010, 0x8),
		PIO_RANGE(0x3f8, 8), /* serial 1 */
	},
	.pci_devices = {
		{ /* Shadow */
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0x0,
			.iommu = 1,
			.bdf = 0x0e << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_MSIX,
			.num_msix_vectors = 16,
			.shmem_regions_start = 0,
			.shmem_dev_id = 1,
			.shmem_peers = 2,
			.shmem_protocol = 0x0002,
		},
		{ /* IVSHMEM-NET */
			.type = JAILHOUSE_PCI_TYPE_IVSHMEM,
			.domain = 0x0,
			.iommu = 1,
			.bdf = 0x0d << 3,
			.bar_mask = JAILHOUSE_IVSHMEM_BAR_MASK_MSIX,
			.num_msix_vectors = 2,
			.shmem_regions_start = 5,
			.shmem_dev_id = 1,
			.shmem_peers = 2,
			.shmem_protocol = JAILHOUSE_SHMEM_PROTO_VETH,
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
	},

	.pci_caps = {
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
		/* PCIDevice: 03:00.1 */
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
