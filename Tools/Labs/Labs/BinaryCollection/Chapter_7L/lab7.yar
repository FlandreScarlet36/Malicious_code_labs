rule lab0701
{
strings:
	$string1 = "Malservice" 
	$string2 = "http://www.malwareanalysisbook.com"
	$string3 = "Internet Explorer 8.0"
condition:
	filesize < 100KB and uint16(0) == 0x5A4D and uint16(uint16(0x3C)) == 0x00004550 and all of them
}
rule lab0702
{
strings:
	$string1 = "http://www.practicalmalwareanalysis.com/cc.html" 
	$string2 = "CoCreateInstance"
condition:
	filesize < 100KB and uint16(0) == 0x5A4D and uint16(uint16(0x3C)) == 0x00004550 and all of them
}
rule lab0703
{
strings:
	$string1 = "127.26.15.13" 
	$string2 = "WARNING_THIS_WILL_DESTORY_YOUR_MACHINE"
	$string3 = "Lab07-03.dll"
condition:
	filesize < 100KB and uint16(0) == 0x5A4D and uint16(uint16(0x3C)) == 0x00004550 and all of them
}