#!/usr/bin/python

# Generate a RS232 type waveform for use in LTSpice 
# for ST interface testing
# source is from https://gist.github.com/speters/cbe0aab8cdb150338410
# modified print to work on my environment / VS code.

data = "asdfg";
bps = 4800; #9600;
num_databits=8;
parity = 'n';
num_stopbits = 1;

lvl_0 = 3.3;
lvl_1 = 0.0;

if type(data) is str:
    data = [data];

out = oldout = 0;
time = 0.0;
timestep = 1.0/bps;
risetime = falltime = timestep / 20.0;
idletime = timestep * (num_databits + 3);

def do_timestep(output, step):
    global time;
    global out, oldout;
    global lvl_0, lvl_1;

    out = output;
    time_diff = 0;

    if oldout!= out:
        if oldout > out:
            # fall
            time_diff = falltime;
        else:
            # rise
            time_diff = risetime;
        lvl = (lvl_0 if oldout == 0 else lvl_1);
        print ("{0:g} {1:g}".format(time, lvl));
        lvl = (lvl_0 if out == 0 else lvl_1);
        print ("{0:g} {1:g}".format((time + time_diff), lvl));

        oldout = out;

    time += step;
    return time;

do_timestep(0,0);

# idle
do_timestep(0, idletime);

for sentence in data:
    # start bit
    out = 1;
    do_timestep(out, timestep);

    for char in sentence:
        # print("# {}").format(char); 
        par = 0;

        for bit in range(0, num_databits):
            out = (ord(char) >> bit) & 1;
            par = bool(parity) ^ bool(out);

            do_timestep(out, timestep);
            
        if parity == 'e':
            # even parity
            out = par;
        elif parity == 'o':
            # odd parity
            out = ~par;
        do_timestep(out, timestep);

        # stop bits
        out = 0;
        do_timestep(out, (timestep * num_stopbits));

    # idle
    out = 0;
    do_timestep(out, idletime);
