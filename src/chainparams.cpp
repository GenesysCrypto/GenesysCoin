// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

#include "chainparamsseeds.h"

//
// Main network
//

// Convert the pnSeeds array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, const unsigned int *data, unsigned int count, int port)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    //for (unsigned int i = 0; i < count; i++) del
	for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
    {
        struct in6_addr ip;
        //memcpy(&ip, data[i].addr, sizeof(ip)); del
		memcpy(&ip, &pnSeed[i], sizeof(ip));
        // CAddress addr(CService(ip, data[i].port)); del
		CAddress addr(CService(ip, port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xe4;
        pchMessageStart[1] = 0xc2;
        pchMessageStart[2] = 0xd8;
        pchMessageStart[3] = 0xe6;
        vAlertPubKey = ParseHex("0486bce1bac0d543f104cbff2bd23680056a3b9ea05e1137d2ff90eeb5e08472eb500322593a2cb06fbf8297d7beb6cd30cb90f98153b5b7cce1493749e41e0284");
        nDefaultPort = 37020; // right Port= 37020
        nRPCPort = 36020;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 24);
		
		/* nPoolMaxTransactions = 3;
        //strSporkKey = "04265602999e3913bc66b390aa3bfc09c84af8e2defd8d1be13cd37a15e141eb5ebbe2513d6ec3a34361f9cd118f548ed34035393cf61c487a24aba6761e9b0867";
        //strMasternodePaymentsPubKey = "04265602999e3913bc66b390aa3bfc09c84af8e2defd8d1be13cd37a15e141eb5ebbe2513d6ec3a34361f9cd118f548ed34035393cf61c487a24aba6761e9b0867";
        strDarksendPoolDummyAddress = "GB5ptSdZ536y75fp3Xjyfqrj4fe7PuTkPL"; */ //reserved

        // Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        //
        //CBlock(hash=000001faef25dec4fbcf906e6242621df2c183bf232f263d0ba5b101911e4563, ver=1, hashPrevBlock=0000000000000000000000000000000000000000000000000000000000000000, hashMerkleRoot=12630d16a97f24b287c8c2594dda5fb98c9e6c70fc61d44191931ea2aa08dc90, nTime=1393221600, nBits=1e0fffff, nNonce=164482, vtx=1, vchBlockSig=)
        //  Coinbase(hash=12630d16a9, nTime=1393221600, ver=1, vin.size=1, vout.size=1, nLockTime=0)
        //    CTxIn(COutPoint(0000000000, 4294967295), coinbase 00012a24323020466562203230313420426974636f696e2041544d7320636f6d6520746f20555341)
        //    CTxOut(empty)
        //  vMerkleTree: 12630d16a9
        const char* pszTimestamp = "http://www.rottentomatoes.com/m/terminator_genisys/";
        std::vector<CTxIn> vin;
        vin.resize(1);
        vin[0].scriptSig = CScript() << 0 << CBigNum(42) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        std::vector<CTxOut> vout;
        vout.resize(1);
        vout[0].SetEmpty();
        CTransaction txNew(1, 1438915672, vin, vout, 0);
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1438915672;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact(); 
        genesis.nNonce   = 11041221;

		
		
		hashGenesisBlock = genesis.GetHash();
		// assert print
        assert(hashGenesisBlock == uint256("0x0000004cae24db4855ee1cb43539b3535c8609afbe34df8e701417f1b39bff12"));
        assert(genesis.hashMerkleRoot == uint256("0x746073a50d9de927f8a0cda618b7b74f13330f8939cc80d3f6a6331861f0382a"));

        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(38); // GSY Publickey Address Start with "G"
        base58Prefixes[SCRIPT_ADDRESS] = list_of(92); //92 - "e"
        base58Prefixes[SECRET_KEY] =     list_of(153); 
		// base58Prefixes[STEALTH_ADDRESS] = list_of(137); // reserved -GSY Stealth Address Start with "x"
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

       
        nLastPOWBlock = 6220;
		
		convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
		// Genesys Seed nodes
		vSeeds.push_back(CDNSSeedData("seednode1", "104.255.33.176"));
        vSeeds.push_back(CDNSSeedData("seednode2", "185.81.166.68")); // 
        vSeeds.push_back(CDNSSeedData("seednode3", "23.227.190.194"));
		vSeeds.push_back(CDNSSeedData("seednode4", "104.156.233.0"));
        vSeeds.push_back(CDNSSeedData("seednode5", "45.63.18.148")); // 
        //vSeeds.push_back(CDNSSeedData("seednode6", "104.167.112.55"));
		//vSeeds.push_back(CDNSSeedData("seednode7", "74.208.227.191"));
        vSeeds.push_back(CDNSSeedData("seednode8", "162.244.28.33")); // 
        vSeeds.push_back(CDNSSeedData("seednode9", "162.244.28.194"));
		vSeeds.push_back(CDNSSeedData("seednode10", "162.244.28.218"));
		vSeeds.push_back(CDNSSeedData("seednode11", "104.255.33.174")); //new
		vSeeds.push_back(CDNSSeedData("seednode12", "194.135.85.43")); //new
		vSeeds.push_back(CDNSSeedData("seednode13", "23.227.190.159")); //new
		
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xcd;
        pchMessageStart[1] = 0xf2;
        pchMessageStart[2] = 0xc0;
        pchMessageStart[3] = 0xef;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        vAlertPubKey = ParseHex("0471dc165db490094d35cde15b1f5d755fa6ad6f2b5ed0f340e3f17f57389c3c2af113a8cbcc885bde73305a553b5640c83021128008ddf882e856336269080496");
        nDefaultPort = 37021;
        nRPCPort = 36021;
        strDataDir = "testnet";

        // Modify the testnet genesis block so the timestamp is valid for a later start.
        genesis.nBits  = 520159231; 
        genesis.nNonce = 11041221;

        assert(hashGenesisBlock == uint256("0x0000004cae24db4855ee1cb43539b3535c8609afbe34df8e701417f1b39bff12"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(97); //"g"
        base58Prefixes[SCRIPT_ADDRESS] = list_of(196); //196
        base58Prefixes[SECRET_KEY]     = list_of(239); //239
		// base58Prefixes[STEALTH_ADDRESS] = list_of(142); // reserved
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x35)(0x87)(0xCF);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x35)(0x83)(0x94);

        convertSeeds(vFixedSeeds, pnTestnetSeed, ARRAYLEN(pnTestnetSeed), nDefaultPort);

        nLastPOWBlock = 0x7fffffff;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    
    bool fTestNet = GetBoolArg("-testnet", false);
    
    if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
