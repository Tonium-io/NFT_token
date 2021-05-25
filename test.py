from tonos_ts4 import ts4
import unittest
import gzip
from PIL import Image
import binascii
eq = ts4.eq

# Initialize TS4 by specifying where the artifacts of the used contracts are located
# verbose: toggle to print additional execution info
class TestPair(unittest.TestCase):
    secret = "bc891ad1f7dc0705db795a81761cf7ea0b74c9c2a93cbf9ac1bad8bd30c9b3b75a4889716084010dd2d013e48b366424c8ba9d391c867e46adce51b18718eb67"
    public = "0x5a4889716084010dd2d013e48b366424c8ba9d391c867e46adce51b18718eb67"

    def test(self):
        ts4.init('./', verbose = True)
        code = ts4.load_code_cell('TONTokenWalletNF.tvc')
        _file = open("photo.jpeg","rb")
        d = _file.read()
        _file_data = gzip.compress(d,compresslevel=9)
        _file_data = binascii.hexlify(_file_data).decode("utf-8")
        #_file_data = binascii.hexlify(b"5423").decode("utf-8")
        constructor = {
                    "name":ts4.Bytes("5423"),
                    "symbol":ts4.Bytes("5423"),
                    "tokenURI":ts4.Bytes("5423"),
                    "decimals":0,
                    "root_public_key":self.public,
                    "wallet_code":code
                }
                # Create root token
        NFTtoken = ts4.BaseContract('RootTokenContractNF',constructor,pubkey=self.public,private_key=self.secret,nickname="NFT root token")
        ts4.dispatch_messages()
        NFTtoken.call_method("mint",dict(tokenId=1,name=ts4.Bytes("54235423"),type=3,data=ts4.Bytes(_file_data[:500])),private_key=self.secret)
        ts4.dispatch_messages()
        NFTtoken.call_method("addBytes",dict(tokenId=1,data=ts4.Bytes(_file_data[500:600])),private_key=self.secret)
        ts4.dispatch_messages()
        print(NFTtoken.call_getter("getInfoToken",dict(tokenId=1)))
        data = NFTtoken.call_getter("getFile",dict(tokenId=1,index=1))
        print(data.raw_)
        print(len(d))
        print(len(bytes.fromhex(data["data"].raw_)) )
        _recieve_data = gzip.decompress(bytes.fromhex(data["data"].raw_))
        _recieve = open("recieve.jpeg","wb")
        
        _recieve.write(_recieve_data)
        _recieve.close()
        Image.open("recieve.jpeg")
if __name__ == '__main__':
    unittest.main()