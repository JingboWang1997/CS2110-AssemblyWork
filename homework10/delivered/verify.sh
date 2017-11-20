#!/bin/bash
if [ `cat list.h | md5sum | cut -f1 -d' '` = "6c31a23d529a37e2aa9d0a6fb698edbd" ]; then
	exit 0
else
	echo "list.h has been modified. Please re-download it from assignments"
	exit 1
fi

