all:
	$(MAKE) -C fire
	$(MAKE) -C plasma

clean:
	$(MAKE) -C fire clean
	$(MAKE) -C plasma clean
