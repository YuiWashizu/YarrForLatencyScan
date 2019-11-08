# YarrForLatencyScan
## 使い方
```
% git clone https://github.com/YuiWashizu/YarrForLatencyScan.git
% cd YarrForLatencyScan/src
% make -j4
% cd scripts
% make
% cd ..
% cp rd53a_test.json.aftertuning ./configs/rd53a_test.json #rd53a_test.json.aftertuningはチューニング後のconfigファイル

% bin/scanConsole -r configs/controller/specCfgExtTrigger.json -c configs/connectivity/example_rd53a_setup.json -s configs/scans/rd53a/std_latencyscan.json -p
% ./convertRaw.sh ./data/xxxxx_std_latencyscan/JohnDoe_data.raw
% source ./setup.sh
% root -l
root[0] .L ./analysis/fromHitTree.C+
root[1] .x ./analysis/LatencyAnalysisTest.C+("./data/xxxxx_std_latencyscan/JohnDoe_data.root")
```
以上のコマンドを入力すれば、`Latency Config`値の分布のplotが現れる。

## code
### `./src/configs/scans/rd53a/std_latencyscan.json`
latencyscanするためのjsonファイル。GlobalRegisterの中のLatencyConfigの値を変化させながら、ソーススキャンを行う。<br>
各値ごとに100回トリガがかかったら、次の値に行く。<br>
"Rd53aGlobalFeedback"の中のパラメータの意味は以下のよう

- `"max"`：LatencyConfigの最大値
- `"min"`：LatencyConfigの最小値

また、トリガ数を変更したい時は`./src/libYarr/StdDataGatherer.cpp`の中の`past_eve`の値を制限している部分（デフォルトで100）を変更すればいい。

### `./src/analysis/LatencyScanTest.C`
`std_latencyscan.json`を走らせた結果を解析し、LatencyConfig値とイベント数の関係をプロットするコード<br>
トリガ数を変更している場合は、34行目の1600という値を16x(トリガ数)に変更する必要がある。

### `./src/scripts/make_HitbusMask.cxx`
configファイルのPixelRegisterの`"Enable"`と`"Hitbus"`を指定して0や1に変更する

|mode||
|:-:|:-:|
|0|50番目のCoreColumnのみをEnable|
|1|Diff FEの下半分のみEnable|
|2|400番目のColumnのみをEnable|
|3|全てのピクセルをDisable|
|4|400番目のColumnの下半分のみをEnable|
|5|全てのピクセルのHitbusのみをDisable|
|6|上半分のHitbusを全てDisable|

## 正常なデータが返ってこない問題
### LatencyScanの分布がおかしい
- Noisyなピクセルが多い
  - チューニングを正しく行えていない
  - NoiseScanでNoisyなピクセルをDisableにしきれていない
- 正常な分布が返ってこないようなら、以下を行い
 ```
 % cd src
 % ./scripts/make_HitbusMask ./configs/rd53a_test.json 1
 % cp ./configs/rd53a_test.json.mask ./configs/rd53a_test.json
 % bin/scanConsole -r configs/controller/specCfgExtTrigger.json -c configs/connectivity/example_rd53a_setup.json -s configs/scans/rd53a/std_latencyscan.json -p
 % ./convertRaw.sh ./data/xxxxx_std_latencyscan/JohnDoe_data.raw
 % source ./setup.sh
 % root -l
 root[0] .L ./analysis/fromHitTree.C+
 root[1] .x ./analysis/LatencyAnalysisTest.C+("./data/xxxxx_std_latencyscan/JohnDoe_data.root")
 ```
 - 以上を行なった結果
   - 正常な分布が返ってきた：Diff FEの上半分がNoisyだったことが原因
   - latencyscanを走らせたが、途中で止まってしまう：そもそもトリガが発行されていない可能性があるため、FWのLogic Analyzerなどでトリガが入力されているか確認する
   - 分布に大きな変化がない、変なまま：`./scripts/make_Hitbusmask`を使って、使用するピクセルをより少なく制限して、再度LatencyScanしてみる
  
