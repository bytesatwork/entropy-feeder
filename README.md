Entropyfeeder
=============

This is a minimal program based on rng-tools, to force feed the Kernel with entropy.

It reads from /dev/hwrng and feeds it to the kernel.

**WARNING, THIS CAN BE A VERY BAD IDEA**
* There are no checks on the quality of the random source
* We feed the Kernel a lot of entropy at a time, this can dominate the entropy pool
* You have to trust your hwrng

## License
This project is licensed under the GPL v2 License - see the [COPYING](COPYING) file for details

