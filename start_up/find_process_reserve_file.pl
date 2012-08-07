#!/usr/bin/perl
use strict;
use warnings;

=begin comment
File        find_process_reserve_file.pl
Brief       
Author      LiJunjie, holysoros@gmail.com
Version     0.00
Date        11-10-27 09:05:07
=cut

my $dir = "/proc/";
opendir my $dh, $dir or die "Can not open $dir: %!\n";
my @items = grep { /\d+/ } readdir $dh;

foreach ( @items ) {
    print "$_:\n";
    system("ls -l $dir$_'/fd'");
}
