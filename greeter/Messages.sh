#! /usr/bin/env bash
$EXTRACTRC -tag-group=none --tag=title --tag=text greet.xml >> rc.cpp || exit 12
$XGETTEXT `find . -name "*.cpp"` -o $podir/SUSEgreeter.pot
