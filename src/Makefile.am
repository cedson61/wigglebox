bin_PROGRAMS = wiggleengine

wiggleengine_SOURCES = \
	wigglebox.cpp \
	rgbdCamera.cpp

wiggleengine_CXXFLAGS = \
	$(AM_CPPFLAGS) \
	$(BOOST_CPPFLAGS) \
    $(FREENECT_CFLAGS) \
	$(OPENCV_CFLAGS)

wiggleengine_LDADD = \
	$(OPENCV_LIBS) \
    $(FREENECT_LIBS) \
	$(BOOST_SYSTEM_LIBS) \
	-lpthread
