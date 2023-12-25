from __future__ import print_function

import grpc

import north_pb2
import north_pb2_grpc


def run():
    channel = grpc.insecure_channel('localhost:50051')
    stub = north_pb2_grpc.GreeterStub(channel)
    response = stub.SayHello(north_pb2.HelloRequest(name='goodspeed lzy'))
    print("Greeter client received: " + response.message)

    pdu_stub = north_pb2_grpc.PduStub(channel)
    response = pdu_stub.Keys(north_pb2.PduKeysRequest())
    print("PDU client received: " + response.keys)

    response = pdu_stub.Meta(north_pb2.PduMetaRequest(key='lzy'))
    print("Meta client received: " + response.key + response.value)


if __name__ == '__main__':
    run()
