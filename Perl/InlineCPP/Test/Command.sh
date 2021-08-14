#!/bin/sh
perl Makefile.PL
ruby RubyScript.rb Makefile -lstdc++
make
#make test