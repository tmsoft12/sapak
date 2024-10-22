import hashlib
import os
import struct

# Gizlin açary döretmek
def create_key(secret_key):
    # Gizlin açaryňyzy SHA-256 bilen hash edýäris
    return hashlib.sha256(secret_key.encode()).digest()

# AES şifrleme funksiyası
def aes_encrypt(data, secret_key):
    key = create_key(secret_key)
    iv = os.urandom(16)  # Tötänleýin Initialization Vector (IV)
    
    # Maglumaty şifrlemek üçin bloklary taýýarla
    data_bytes = data.encode()
    padding_length = 16 - (len(data_bytes) % 16)
    padded_data = data_bytes + bytes([padding_length]) * padding_length

    encrypted_data = bytearray(len(padded_data))
    for i in range(0, len(padded_data), 16):
        block = padded_data[i:i+16]
        for j in range(16):
            encrypted_data[i+j] = block[j] ^ key[j % len(key)]  # XOR operasiýasy bilen şifrleýäris

    return iv + encrypted_data  # IV we şifrlenen maglumat

# AES dekodirleme funksiyası
def aes_decrypt(encrypted_data, secret_key):
    key = create_key(secret_key)
    iv = encrypted_data[:16]  # IV-ny alýarys
    encrypted_data = encrypted_data[16:]  # Şifrlenen maglumatlary alýarys

    decrypted_data = bytearray(len(encrypted_data))
    for i in range(0, len(encrypted_data), 16):
        block = encrypted_data[i:i+16]
        for j in range(16):
            decrypted_data[i+j] = block[j] ^ key[j % len(key)]  # XOR operasiýasy bilen açýarys

    # Paddingi aýyr
    padding_length = decrypted_data[-1]
    return decrypted_data[:-padding_length].decode()  # Dekodirlenen maglumat

# Maglumatyňyzy giriziň
original_data = "salam"
secret_key = "gizlinAcar"

# Şifrlemek
encrypted_data = aes_encrypt(original_data, secret_key)
print(f"Şifrlenen maglumat: {encrypted_data.hex()}")

# Dekodirlemek
decrypted_data = aes_decrypt(encrypted_data, secret_key)
print(f"Dekodirlenen maglumat: {decrypted_data}")
