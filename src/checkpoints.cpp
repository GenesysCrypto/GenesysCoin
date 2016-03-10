// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "txdb.h"
#include "main.h"
#include "uint256.h"


static const int nCheckpointSpan = 2000;

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        // (0,	Params().HashGenesisBlock() )
		( 0,		uint256("0x0000004cae24db4855ee1cb43539b3535c8609afbe34df8e701417f1b39bff12"))
		( 535, uint256("0x00000000000001d871656bedaf2a9b091761fb47165535c019349807e9702f6d"))
		( 1156, uint256("0x0000000000000ed34e6cd85aabc0b73f0e16bdafec9e9ac43328546fd5447684"))
		( 2391, uint256("0x000000000000069b249a0a65cbecef0dc29738c1a7f11f1526667fb99dc89fa0"))
		( 10264, uint256("0x4c1d7a989ab40e3e8db40710062ffba4740ed3982c4118dc7ff06f9ee42a385e"))
		( 24297, uint256("0x4deee90ff76c83cbe5419e2e6ac0ed8a1cfffe29687c62603d909a87031acdb4"))
		( 32436, uint256("0xe2706c3a2baf84eca521e3a1843266978893b7b97495e2e6199bceeb54667113"))
		( 47435, uint256("0x052203887414519eeaaa5794a222d304237099a4f97a1bd8a4957b88bb0b6cf6"))
		( 78278, uint256("0xf07215c033903af1396896d1f68d4d46f2b020b55857c169e4fef0e5a62a1939"))
		( 82745, uint256("0xae50c3d9b96a82177ab94643f5f38d22b686ba0f83926b4f983026c87e913252"))
		( 95129, uint256("0xdb1851e315f3862014f4c4351653db74fb3f197698a514ffcea75d0aa1a83c03"))
		( 110482, uint256("0xab0bf8ced6fbdb0047c4c1129adf5d6e59c32e20345fd70e847acedd0da5df16"))
		( 128210, uint256("0xe6be0c116830e9a4c7e1ad785cd900230dd22c2e5df0abd3a7e4961869665623"))
		( 138214, uint256("0x02636de7742035052ab44ebf2266d4c062b25332831a911a53052f4684e4e84b"))
		( 265134, uint256("0xa162a6ac1dbd90b31952e33231ad56e30c33da0b96feeb74e38973226ad7990c"))
		( 279382, uint256("0x8fc98095717803e9ad9c528d5c8798b61d1052a8fb0a5c957aee77490b2f4c8a"))
		// ( ******, uint256("0x"))
		// ( ******, uint256("0x"))
		// ( ******, uint256("0x"))
		// ( ******, uint256("0x"))
		;

    // TestNet has no checkpoints
    static MapCheckpoints mapCheckpointsTestnet;

    bool CheckHardened(int nHeight, const uint256& hash)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        MapCheckpoints::const_iterator i = checkpoints.find(nHeight);
        if (i == checkpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        if (checkpoints.empty())
            return 0;
        return checkpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        MapCheckpoints& checkpoints = (TestNet() ? mapCheckpointsTestnet : mapCheckpoints);

        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, checkpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }

    // Automatically select a suitable sync-checkpoint 
    const CBlockIndex* AutoSelectSyncCheckpoint()
    {
        const CBlockIndex *pindex = pindexBest;
        // Search backward for a block within max span and maturity window
        while (pindex->pprev && pindex->nHeight + nCheckpointSpan > pindexBest->nHeight)
            pindex = pindex->pprev;
        return pindex;
    }

    // Check against synchronized checkpoint
    bool CheckSync(int nHeight)
    {
        const CBlockIndex* pindexSync = AutoSelectSyncCheckpoint();
        if (nHeight <= pindexSync->nHeight){
            return false;
        }
        return true;
    }
}
