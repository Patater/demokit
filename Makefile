all:
	$(MAKE) -C fire
	$(MAKE) -C plasma
	$(MAKE) -C stars
	$(MAKE) -C tunnel

clean:
	$(MAKE) -C fire clean
	$(MAKE) -C plasma clean
	$(MAKE) -C stars clean
	$(MAKE) -C tunnel clean
