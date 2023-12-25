
安装 gRPC
	sudo python -m pip install grpcio
安装 gRPC tools
	Python gPRC tools 包含 protocol buffer 编译器和用于从 .proto 文件生成服务端和客户端代码的插件
	sudo python -m pip install grpcio-tools

	sudo python -m pip install protobuf
	
编译
	python -m grpc_tools.protoc -I./ --python_out=. --grpc_python_out=. ./north.proto


