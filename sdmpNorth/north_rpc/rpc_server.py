from concurrent import futures
import time

import grpc

import north_pb2
import north_pb2_grpc

_ONE_DAY_IN_SECONDS = 60 * 60 * 24


class Pdu(north_pb2_grpc.PduServicer):
    def Keys(self, request, context):
        return north_pb2.PduKeysReply(keys='Hello, lzy!')

    def Meta(self, request, context):
        return north_pb2.PduMetaReply(key='pdu' + request.key, value='luozhiyong')


class Greeter(north_pb2_grpc.GreeterServicer):
	# 工作函数
    def SayHello(self, request, context):
        return north_pb2.HelloReply(message='Hello, %s!' % (request.name))


def serve():
    # gRPC 服务器
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    north_pb2_grpc.add_PduServicer_to_server(Pdu(), server)
    north_pb2_grpc.add_GreeterServicer_to_server(Greeter(), server)

    server.add_insecure_port('[::]:50051')
    server.start()  # start() 不会阻塞，如果运行时你的代码没有其它的事情可做，你可能需要循环等待。
    try:
        while True:
            time.sleep(_ONE_DAY_IN_SECONDS)
    except KeyboardInterrupt:
        server.stop(0)

if __name__ == '__main__':
    serve()