#!/usr/bin/perl
use strict;
use warnings;

=begin comment
File        ophir.pl
Brief       
Author      sunshine, mxdhlj@163.com
Version     0.00
Date        11-06-27 09:04:48
=cut

my $cycleNum = 0;
sub ophir
{
    $cycleNum ++;
    return(0) if($cycleNum >= 51); 
    my ($num1,$num2) = @_;
    print($num1, " ", $num2," ") if($cycleNum == 1);
    print $num2." " if($cycleNum != 1);
    return ( ophir($num2, $num1+$num2 ));
}
ophir(0, 1);
