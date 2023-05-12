SMALL HTTPS SERVER for windows/linux

based on Mongoose networking library for C/C++. binary is compressed with upx for even smaller size of 497K.

FEATURES: 
	can serve files from 'FILES' subfolder. its basically 'hello world' for https server with further possibilities to expand.

INSTRUCTIONS:
	- place your key.pem,cert.pem (certificate keys, can be generated using openssl) in same folder together with binary .exe file.
	- start the binary
	- files are served from 'FILES' subfolder
	- to test it go https://127.0.0.1/ ( if your certificates are self signed you will need 'accept the risk and continue' in your browser)
	
BUILD INSTRUCTIONS:
	-You need 'gcc.exe' from MinGW64 compiler for windows to be in path.
	-unzip sources and run compile.bat to create server binary main.exe. Already included is mbedtls library with build instructions.

