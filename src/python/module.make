# To compile with the embedded python interpreter set 
# the variable ABC_PYTHON to point to the python executable
# 
# Examples:
# make ABC_PYTHON=/usr/bin/python
# make ABC_PYTHON=/usr/bin/python2.5
# 
# To build the Python extension build the target pyabc
# To create a package of ABC with embedded Python use the target pyabc.tgz

ifdef ABC_PYTHON

	# get the directory containing this file
	ABC_PYTHON_FILES_PREFIX := $(dir $(lastword $(MAKEFILE_LIST)))

	ABC_SWIG := swig
	ABC_PYTHON_CONFIG := $(ABC_PYTHON)-config
	ABC_PYTHON_CFLAGS := $(shell $(ABC_PYTHON_CONFIG) --includes) -DABC_PYTHON_EMBED=1
	ABC_PYTHON_LDFLAGS := $(shell $(ABC_PYTHON_CONFIG) --ldflags)

	CFLAGS += $(ABC_PYTHON_CFLAGS)
	CXXFLAGS += $(ABC_PYTHON_CFLAGS)
	LIBS += $(ABC_PYTHON_LDFLAGS)

	ABC_PYTHON_SRC := $(ABC_PYTHON_FILES_PREFIX)/pyabc_wrap.c
	
	SRC += $(ABC_PYTHON_SRC)
	
	GARBAGE += \
		$(ABC_PYTHON_SRC) \
		$(ABC_PYTHON_SRC:_wrap.c=.py) \
		$(ABC_PYTHON_SRC:_wrap.c=.pyc) \
		$(ABC_PYTHON_FILES_PREFIX)/build \
		$(ABC_PYTHON_FILES_PREFIX)/dist \
		pyabc.tgz

%_wrap.c %.py : %.i
	$(ABC_SWIG) -python -outdir $(<D) $<

.PHONY: pyabc_extension_build

pyabc_extension_build : lib$(PROG).a $(ABC_PYTHON_SRC) $(ABC_PYTHON_SRC:_wrap.c=.py)
	( cd $(ABC_PYTHON_FILES_PREFIX) && rm -rf build/ )	
	( cd $(ABC_PYTHON_FILES_PREFIX) && python setup.py build )
	
.PHONY: pyabc_extension_install

pyabc_extension_install : pyabc_extension_build	
	( cd $(ABC_PYTHON_FILES_PREFIX) && python setup.py install --user )
	
.PHONY: pyabc_extension_bdist

pyabc_extension_bdist : pyabc_extension_build	
	( cd $(ABC_PYTHON_FILES_PREFIX) && python setup.py bdist )
	
pyabc.tgz : $(PROG) $(ABC_PYTHON_SRC:_wrap.c=.py) $(ABC_PYTHON_FILES_PREFIX)/abc.sh $(ABC_PYTHON_FILES_PREFIX)/package.py
	$(ABC_PYTHON) $(ABC_PYTHON_FILES_PREFIX)/package.py \
		--abc=$(PROG) \
		--abc_sh=$(ABC_PYTHON_FILES_PREFIX)/abc.sh \
		--pyabc=$(ABC_PYTHON_SRC:_wrap.c=.py) \
		--out=$@ \
		$(ABC_PYTHON_OPTIONS)

endif
