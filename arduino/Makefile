# This script creates the PowerManagementUnit Arduino based library files.

LIBRARYDIRNAME=PowerManagementUnit
RELEASEDIRNAME=prebuild
CONFIGDIRNAME=config

.DEFAULT_GOAL := prebuild

prebuild: library.properties.template ../include/powermu/PowerMU.h ../src/powermu/PowerMU.c
	@echo "> Preparing header and source files"
	mkdir -p "$(RELEASEDIRNAME)/$(LIBRARYDIRNAME)"
	find ../include/ -type f -name *.h -exec cp {} "$(RELEASEDIRNAME)/$(LIBRARYDIRNAME)/" \;
	find ../src/ -type f -name *.c -exec cp {} "$(RELEASEDIRNAME)/$(LIBRARYDIRNAME)/" \;
	cp ./library.properties.template "$(RELEASEDIRNAME)/$(LIBRARYDIRNAME)/library.properties"

clean:
	@echo "> Cleaning header and source files"
	rm -Rf "$(RELEASEDIRNAME)"
