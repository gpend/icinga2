#!/bin/sh
ICINGA2CONFDIR=@CMAKE_INSTALL_FULL_SYSCONFDIR@/icinga2

TOOL=$(basename -- $0)

if [ "$TOOL" != "icinga2-enable-feature" -a "$TOOL" != "icinga2-disable-feature" ]; then
	echo "Invalid tool name ($TOOL). Should be 'icinga2-enable-feature' or 'icinga2-disable-feature'."
	exit 1
fi

if [ -z "$1" ]; then
	echo "Syntax: $0 <feature>"

	if [ "$TOOL" = "icinga2-enable-feature" ]; then
		echo "Enables the specified feature."
	else
		echo "Disables the specified feature."
	fi

	echo
	echo -n "Available features: "

	for file in $ICINGA2CONFDIR/features-available/*.conf; do
		echo -n "$(basename -- $file .conf) "
	done

	echo

	exit 1
fi

FEATURE=$1

if [ ! -e $ICINGA2CONFDIR/features-available/$FEATURE.conf ]; then
	echo "The feature '$FEATURE' does not exist."
	exit 1
fi

if [ "$TOOL" = "icinga2-enable-feature" ]; then
	if [ -e $ICINGA2CONFDIR/features-enabled/$FEATURE.conf ]; then
		echo "The feature '$FEATURE' is already enabled."
		exit 0
	fi

	ln -s ../features-available/$FEATURE.conf $ICINGA2CONFDIR/features-enabled/

	echo "Module '$FEATURE' was enabled."
elif [ "$TOOL" = "icinga2-disable-feature" ]; then
	if [ ! -e $ICINGA2CONFDIR/features-enabled/$FEATURE.conf ]; then
		echo "The feature '$FEATURE' is already disabled."
		exit 0
	fi

	rm -f $ICINGA2CONFDIR/features-enabled/$FEATURE.conf

	echo "Module '$FEATURE' was disabled."
fi

echo "Make sure to restart Icinga 2 for these changes to take effect."
exit 0
