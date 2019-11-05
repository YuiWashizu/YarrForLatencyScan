# YarrForLatencyScan
```
% git clone https://github.com/YuiWashizu/YarrForLatencyScan.git
% cd YarrForLatencyScan/src
% make -j4
% cd scripts
% make

% bin/scanConsole -r configs/controller/specCfgExtTrigger.json -c configs/connectivity/example_rd53a_setup.json -s configs/scans/rd53a/std_latencyscan.json -p
% ./convertRaw.sh ./data/xxxxx_std_latencyscan/JohnDoe_data.raw
% source ./setup.sh
% root -l
root[0] .L ./analysis/fromHitTree.C+
root[1] .x ./analysis/LatencyAnalysis.C+("./data/xxxxx_std_latencyscan/JohnDoe_data.root")
```
