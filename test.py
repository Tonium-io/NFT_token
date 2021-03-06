from tonos_ts4 import ts4
import unittest
import gzip
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

        #_file_data = binascii.hexlify(b"5423").decode("utf-8")
        constructor = {
                    "name":ts4.Bytes("5423"),
                    "symbol":ts4.Bytes("5423"),
                    "decimals":0,
                    "root_public_key":self.public,
                    "wallet_code":code
                }
                # Create root token
        NFTtoken = ts4.BaseContract('RootTokenContractNF',constructor,pubkey=self.public,private_key=self.secret,nickname="NFT root token")
        ts4.dispatch_messages()
        NFTtoken.call_method("mint",dict(tokenId=1,name=ts4.Bytes("54235423"),jsonMeta=ts4.Bytes("5423"),data=ts4.Address("0:" + "0" * 64)),private_key=self.secret)
        ts4.dispatch_messages()
        print(NFTtoken.call_getter("getInfoToken",dict(tokenId=1)))
if __name__ == '__main__':
    unittest.main()
