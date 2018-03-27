roundLength = 290000;

bfile = fopen('../DPA/traces.bin', 'rb');
round_1 = fread(bfile, roundLength, 'uint8');
fseek(bfile, roundOffset * 99, 'cof');
round_100 = fread(bfile, roundLength, 'uint8') + 192;
fseek(bfile, roundOffset * 99, 'cof');
round_200 = fread(bfile, roundLength, 'uint8') + 384;
fclose(bfile);

###########################
figure(1);
x = 1:length(round_1);
plot (x, round_1, x, round_100, x, round_200);
xlabel ("no. sample");
ylabel ("sample value [0-255]");
title ("Complete traces 1st, 100th, 200th");

###########################
figure(2);
hist(round_1);
xlabel ("Sample value [0-255]");
colormap (summer ());
ylabel ("Value count");
title ("Histogram of observed value");

###########################
rounds = [];
bfile = fopen('../DPA/traces.bin', 'rb');
for n = 1:100
  round = fread(bfile, roundLength, 'uint8')';
  rounds = [rounds; round];
end
fclose(bfile);
meanrounds = mean(rounds);

###
figure(3);
startmean = meanrounds(:,1:25000);
x = 1:length(startmean);
plot (x, startmean);
xlabel ("no. sample");
ylabel ("sample value [0-255]");
title ("Mean of 100 samples - start");

###
figure(4);
centermean = meanrounds(:,100000:125000);
x = 1:length(centermean);
plot (x, centermean);
xlabel ("no. sample");
ylabel ("sample value [0-255]");
title ("Mean of 100 samples - center");

###
figure(5);
endmean = meanrounds(:,end-25000:end);
x = 1:length(endmean);
plot (x, endmean);
xlabel ("no. sample");
ylabel ("sample value [0-255]");
title ("Mean of 100 samples - end");
