import socket
import threading
import json

HOST = '127.0.0.1'
PORT = 12345

server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((HOST, PORT))
server.listen()

clients = []
names = []
keys = []

def broadcast(message):
    for client in clients:
        client.send(message)

def handle(client):
    while True:
        try:
            message = client.recv(1024)
            if b'disconnect' in message:
                # go to except
                assert 1 != 1
            
            elif message != b'':
                print(json.dumps({'received': message.decode()}))
                broadcast(message)

        except:
            index = clients.index(client)
            clients.remove(client)
            client.close()

            name = names[index]
            names.remove(name)
            break

def run():
    while len(clients) < 2:
        client, address = server.accept()
        clients.append(client)

        # asking for nickname
        client.send('> Enter your name: '.encode())
        name = client.recv(1024).strip().decode()
        names.append(name)

        print(json.dumps({'Address': str(address), 'Name':name, 'status':'Connected'}))

        # asking for pubKey
        client.send('> Enter your pubKey ("Px, Py"): '.encode())
        pubKey = client.recv(1024).strip().decode()
        keys.append(pubKey)

        print(json.dumps({'Address': str(address), 'Name':name, 'pubKey':pubKey}))

        thread = threading.Thread(target=handle, args=(client,))
        thread.start()
    
    clients[0].send(f"{names[1]}'s pubKey: {keys[1]}".encode())
    clients[1].send(f"{names[0]}'s pubKey: {keys[0]}".encode())

if __name__ == '__main__':
    print(f'[!] Listenning to port {PORT}...')
    run()
