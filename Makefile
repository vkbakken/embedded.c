clean_tmp_files:
	find . -name "*.o" -type f -delete
	find . -name "*.hex" -type f -delete
	find . -name "*.elf" -type f -delete
	find . -name "*.lst" -type f -delete
	find . -name "*.map" -type f -delete
