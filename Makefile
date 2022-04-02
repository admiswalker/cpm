

FORCE_TO_MAKE:
	cd cpm; make -j


clean:
	@cd cpm; make clean
	@rm -f exe
#	@rm -fr cpm_env

