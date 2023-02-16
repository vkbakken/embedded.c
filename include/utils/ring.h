#ifndef RING_H_INCLUDED
#define RING_H_INCLUDED

#include <stdbool.h>

#include <compiler.h>


struct ring_head {
	//! Offset of the next free entry in the buffer.
	unsigned int head;
	//! Offset of the first used entry in the buffer.
	unsigned int tail;
};


#ifdef CONFIG_RING_DEBUG
#include <util.h>

ERROR_FUNC(ring_priv_bad_constant_size, "Ring size must be a power of two")

static inline void ring_priv_bad_size(unsigned int size)
{
	dbg_error("Bad ring size %u: Not a power of two!\n", size);
}

static inline void ring_priv_check_size(unsigned int size)
{
	if (!is_power_of_two(size)) {
		if (is_constant(size))
			ring_priv_bad_constant_size(size);
		else
			ring_priv_bad_size(size);
	}
}
#else
static inline void ring_priv_check_size(unsigned int size)
{

}
#endif


static inline unsigned long ring_get_head(struct ring_head *ring,
		unsigned int ring_size)
{
	ring_priv_check_size(ring_size);

	return ring->head & (ring_size - 1);
}


static inline unsigned long ring_get_tail(struct ring_head *ring,
		unsigned int ring_size)
{
	ring_priv_check_size(ring_size);

	return ring->tail & (ring_size - 1);
}


static inline unsigned int ring_entries_used(struct ring_head *ring)
{
	return ring->head - ring->tail;
}


static inline unsigned int ring_entries_used_before_end(struct ring_head *ring,
		unsigned int ring_size)
{
	unsigned int head = ring->head;
	unsigned int tail = ring->tail;

	ring_priv_check_size(ring_size);

	if ((head ^ tail) & ring_size)
		return ring_size - (tail & (ring_size - 1));
	else
		return head - tail;
}


static inline unsigned int ring_entries_unused(struct ring_head *ring,
		unsigned int ring_size)
{
	return ring_size - ring_entries_used(ring);
}


static inline unsigned int ring_entries_unused_before_end(
		struct ring_head *ring, unsigned int ring_size)
{
	unsigned int head = ring->head;
	unsigned int tail = ring->tail;

	ring_priv_check_size(ring_size);

	if ((head ^ tail) & ring_size)
		return ring_size + tail - head;
	else
		return ring_size - (head & (ring_size - 1));
}


static inline bool ring_is_empty(struct ring_head *ring)
{
	return ring->head == ring->tail;
}


static inline bool ring_is_full(struct ring_head *ring,
		unsigned int ring_size)
{
	return ring_entries_used(ring) == ring_size;
}


static inline void ring_insert_entries(struct ring_head *ring,
		unsigned int nr_entries)
{
	barrier();
	ring->head += nr_entries;
}


static inline void ring_extract_entries(struct ring_head *ring,
		unsigned int nr_entries)
{
	barrier();
	ring->tail += nr_entries;
}


static inline void ring_reset(struct ring_head *ring)
{
	ring->head = ring->tail = 0;
}
#endif /* RING_H_INCLUDED */
