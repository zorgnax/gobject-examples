CFLAGS  = `pkg-config --cflags gobject-2.0` -I. -g
LDFLAGS = `pkg-config --libs gobject-2.0` -L. -ltap
PROGS   = 01-media-from-book/media 02-point-inheritance/dopoints 03-order-of-callbacks/doorders 04-define-type-macros/dot 05-bank-account/robthebank 06-binary-tree/testbtree 07-currency-interfaces/launder
BPROGS  = media dopoints doorders dot robthebank testbtree launder

all: ${PROGS}

clean:
	rm -rvf ${PROGS} ${BPROGS} ${patsubst %, %.dSYM, ${PROGS}}

01-media-from-book/media: 01-media-from-book/cleanable.c 01-media-from-book/cleanable.h 01-media-from-book/media.c
	gcc ${CFLAGS} -o $@ 01-media-from-book/cleanable.c 01-media-from-book/media.c ${LDFLAGS}
	cp -v 01-media-from-book/media .

02-point-inheritance/dopoints: 02-point-inheritance/dopoints.c 02-point-inheritance/point.c 02-point-inheritance/point.h 02-point-inheritance/point3d.c 02-point-inheritance/point3d.h
	gcc ${CFLAGS} -o $@ 02-point-inheritance/dopoints.c 02-point-inheritance/point.c 02-point-inheritance/point3d.c ${LDFLAGS}
	cp -v 02-point-inheritance/dopoints .

03-order-of-callbacks/doorders: 03-order-of-callbacks/doorders.c 03-order-of-callbacks/order.c 03-order-of-callbacks/order.h 03-order-of-callbacks/order2.c 03-order-of-callbacks/order2.h
	gcc ${CFLAGS} -o $@ 03-order-of-callbacks/doorders.c 03-order-of-callbacks/order.c 03-order-of-callbacks/order2.c ${LDFLAGS}
	cp -v 03-order-of-callbacks/doorders .

04-define-type-macros/dot: 04-define-type-macros/dot.c 04-define-type-macros/handy.h
	gcc ${CFLAGS} -o $@ 04-define-type-macros/dot.c ${LDFLAGS}
	cp -v 04-define-type-macros/dot .

05-bank-account/robthebank: 05-bank-account/bankaccount.c 05-bank-account/bankaccount.h 05-bank-account/checkingaccount.c 05-bank-account/checkingaccount.h 05-bank-account/robthebank.c
	gcc ${CFLAGS} -o $@ 05-bank-account/bankaccount.c 05-bank-account/checkingaccount.c 05-bank-account/robthebank.c ${LDFLAGS}
	cp -v 05-bank-account/robthebank .

06-binary-tree/testbtree: 06-binary-tree/binarytree.c 06-binary-tree/binarytree.h 06-binary-tree/testbtree.c
	gcc ${CFLAGS} -o $@ 06-binary-tree/binarytree.c 06-binary-tree/testbtree.c ${LDFLAGS}
	cp -v 06-binary-tree/testbtree .

07-currency-interfaces/launder: 07-currency-interfaces/comparable.c 07-currency-interfaces/comparable.h 07-currency-interfaces/eq.c 07-currency-interfaces/eq.h 07-currency-interfaces/launder.c 07-currency-interfaces/printable.c 07-currency-interfaces/printable.h 07-currency-interfaces/uscurrency.c 07-currency-interfaces/uscurrency.h
	gcc ${CFLAGS} -o $@ 07-currency-interfaces/comparable.c 07-currency-interfaces/eq.c 07-currency-interfaces/launder.c 07-currency-interfaces/printable.c 07-currency-interfaces/uscurrency.c ${LDFLAGS}
	cp -v 07-currency-interfaces/launder .


