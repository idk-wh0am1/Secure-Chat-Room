CC = g++
CFLAGS = -DNDEBUG -g3 -O2 -Wall -Wextra

.PHONY ECDH: ECDH/key_generate.cpp
	@echo ">>> Compiling ECDH/key_generate.cpp..."
	$(CC) $(CFLAGS) ECDH/key_generate.cpp -o ECDH/key_generate -l:libcryptopp.a

	@echo ">>> Compiling ECDH/key_exchange.cpp..."
	$(CC) $(CFLAGS) ECDH/key_exchange.cpp -o ECDH/key_exchange -l:libcryptopp.a

clean:
	@echo ">>> Cleaning compiled file..."
	rm -rf ECDH/key_generate ECDH/key_exchange