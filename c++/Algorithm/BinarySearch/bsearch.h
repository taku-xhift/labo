#ifndef _LINUX_BSEARCH_H
#define _LINUX_BSEARCH_H

// #include <linux/types.h>

void *bsearch(const void *key, const void *base, std::size_t num, std::size_t size,
	      int (*cmp)(const void *key, const void *elt));

#endif /* _LINUX_BSEARCH_H */
