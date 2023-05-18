import socket
import ecdh

HOST = input("[+] HOST: ")
PORT = int(input("[+] PORT: "))

print(f'[!] Connecting to ({HOST, PORT})...')
client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client.connect((HOST, PORT))

name = input("> What's your name? ").strip()
ecc = ecdh.ECDH()
privKey, pubKey = ecc.generate_key()
other_pubKey = ""

def run():
    while True:
        try:
            message = client.recv(1024)
            if b'Enter your name' in message:
                client.send(name.encode())
            
            elif b'Enter your pubKey' in message:
                client.send(pubKey.encode())
            
            elif b"'s pubKey: " in message:
                other_pubKey = message.split(b"'s pubKey: ")[-1].strip().decode()
                key = ecc.exchange_key(other_pubKey)
                print(f"[DEBUG] Exchange key sucessfully, shared key = {key}")
                print("Goodbye!...")
                client.close()                
                exit()

            else:
                print(message.decode().strip())
            
        except:
            client.close()
            break

if __name__ == '__main__':
    run()