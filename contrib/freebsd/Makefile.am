sync-with-kernel:
	rm -rf .pc

	for i in input.h ivtv.h uinput.h videodev2.h dvb/{audio.h,ca.h,dmx.h,frontend.h,net.h,osd.h,version.h,video.h}; do \
	    mkdir -p include/linux/$$(dirname $$i); \
	    cp $(KERNEL_DIR)/include/linux/$$i include/linux/$$i; \
	done

	mkdir -p include/media
	cp $(KERNEL_DIR)/include/media/v4l2-chip-ident.h include/media/

	for i in ivtv.h uinput.h videodev2.h dvb/{audio.h,ca.h,dmx.h,frontend.h,net.h,osd.h,version.h,video.h}; do \
	    sed -e 's/__u8/uint8_t/g' -e 's/__u16/uint16_t/g' -e 's/__u32/uint32_t/g' -e 's/__u64/uint64_t/g' -e 's/__s8/int8_t/g' -e 's/__s16/int16_t/g' -e 's/__s32/int32_t/g' -e 's/__s64/int64_t/g' -e 's/__le32/uint32_t/g' -e 's/__user//g' -i include/linux/$$i; \
	done

	quilt push -a
