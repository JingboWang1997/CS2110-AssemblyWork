#!/bin/bash
if [ `cat array_list.h | md5sum | cut -f1 -d' '` = "e6531407a5f6b0c08fff7fcb7cdbb843" ]; then
	exit 0
else
	echo "array_list.h has been modified. Please re-download it from assignments"
	exit 1
fi

