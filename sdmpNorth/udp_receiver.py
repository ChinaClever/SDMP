import socket
import threading
import json


class UDPReceiver:
    def __init__(self, ip, port):
        self.ip = ip
        self.port = port
        self.socket = None
        self.thread = None
        self.running = False
        self.packet_dict = {}

    def start(self):
        self.socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        self.socket.bind((self.ip, self.port))
        self.running = True

        print(f"UDP receiver started. Listening on {self.ip}:{self.port}")
        self.thread = threading.Thread(target=self.receive_thread)
        self.thread.daemon = True  # 设置线程为守护线程
        self.thread.start()

    def stop(self):
        self.running = False
        self.thread.join()
        self.socket.close()
        print("UDP receiver stopped.")

    def receive_thread(self):
        while self.running:
            data, addr = self.socket.recvfrom(1024*5)
            json_data = json.loads(data.decode('utf-8'))
            self.insert_packet(addr[0], json_data)
            # print(f"Received data from {sender_ip}: {json_data}")

    def insert_packet(self, sender_ip, json_data):
        uid = json_data.get('uuid', sender_ip)
        self.packet_dict[uid] = json_data

    def get_keys(self):
        return self.packet_dict.keys()

    def get_packet(self, uid):
        return self.packet_dict.get(uid, None)


# 示例用法
if __name__ == "__main__":
    receiver = UDPReceiver("127.0.0.1", 12345)
    receiver.start()

    # 其他操作

    receiver.stop()