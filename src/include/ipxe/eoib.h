#ifndef _IPXE_EOIB_H
#define _IPXE_EOIB_H

/** @file
 *
 * Ethernet over Infiniband
 *
 */

FILE_LICENCE ( GPL2_OR_LATER_OR_UBDL );

#include <stdint.h>
#include <byteswap.h>
#include <ipxe/netdevice.h>
#include <ipxe/infiniband.h>
#include <ipxe/ib_mcast.h>

/** An EoIB header */
struct eoib_header {
	/** Signature */
	uint16_t magic;
	/** Reserved */
	uint16_t reserved;
} __attribute__ (( packed ));

/** EoIB magic signature */
#define EOIB_MAGIC 0x8919

/** An EoIB device */
struct eoib_device {
	/** Name */
	const char *name;
	/** Network device */
	struct net_device *netdev;
	/** Underlying Infiniband device */
	struct ib_device *ibdev;
	/** List of EoIB devices */
	struct list_head list;
	/** Broadcast address */
	struct ib_address_vector broadcast;

	/** Completion queue */
	struct ib_completion_queue *cq;
	/** Queue pair */
	struct ib_queue_pair *qp;
	/** Broadcast group membership */
	struct ib_mc_membership membership;

	/** Peer cache */
	struct list_head peers;
};

extern int eoib_create ( struct ib_device *ibdev, const uint8_t *hw_addr,
			 struct ib_address_vector *broadcast,
			 const char *name );
extern struct eoib_device * eoib_find ( struct ib_device *ibdev,
					const uint8_t *hw_addr );
extern void eoib_destroy ( struct eoib_device *eoib );

#endif /* _IPXE_EOIB_H */