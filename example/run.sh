#!/bin/bash

runname=test

basedir=$( pwd )
pricegen=${basedir}/../underlying_model/gbm.cc
option=${basedir}/../option_pricing/european_call.cc

s0=1.0
T=100 #day
r=0.01

# gbm
mu=0.03
sigma=0.1

# heston
theta=0.01
kappa=0.01
xi=0.1

# 0. set parameters

[ ! -d ${runname} ] && mkdir ${runname}
cd ${runname}
[ ! -f ${runname}.log ] && echo "s0,r,mu,sigma,theta,alpha,kappa,xi,T" >> ${runname}.log

echo "${s0},${r},${mu},${sigma},${theta},${alpha},${kappa},${xi},${T}" >> ${runname}.log

# 1. analytic

sed "s/ANAL *$/ANAL 1" ${pricegen}
sed "s/MC *$/MC 0" ${pricegen}
sed "s/ANAL *$/ANAL 1" ${option}
sed "s/MC *$/MC 0" ${option}

g++ ${pricegen} -std=c++2a -mtune=native -march=native -O3 -o gbm_anal
echo ${m} ${runname} | ./${pricegen}
g++ ${option} -std=c++2a -mtune=native -march=native -O3 -o option_anal
echo ${m} ${runname} | ./${option} 

# 2. MC for option pricing

sed "s/ANAL *$/ANAL 0" ${option}
sed "s/MC *$/MC 1" ${option}
g++ ${option} -std=c++2a -mtune=native -march=native -O3 -o european_call_mc

for m in 100 200 400 800 1600 3200 6400 12800
do
	echo ${m} ${runname} | ./european_call_mc
done

# 3. MC both for price timeseries and option pricing

sed "s/ANAL *$/ANAL 0" ${pricegen}
sed "s/MC *$/MC 1" ${pricegen}
g++ ${pricegen} -std=c++2a -mtune=native -march=native -O3 -o gbm_em

for m in 100 200 400 800 1600 3200 6400 12800
do
	echo ${m} ${runname} | ./gbm_em
	echo ${m} ${runname} | ./european_call_mc
done
