#include <stdio.h>
#include <stdlib.h>

	struct SampleInfo
	{
	char Name[22];
	int Len;
	short FineTune;
	short Vol;
	int RepStart;
	int RepLen;
	} Sample[31];

	short SongLen;
	short Dummy;
	int SongPos[127];
	char ModSig[5];

	char Use[]="\nUsage:  modinfo <modname.mod>\n"
		   "This will give you more info than you will ever want\n"
		   "about a .mod file -- best to redirect to a file or a\n"
		   "utility like \"more.\"\n\nWritten by Captain Sarcastic.\n"
		   "kkoller@nyx.cs.du.edu\n";

	char Head[]="\nModInfo 1.0a by Captain Sarcastic\n"
		    "Generates ProTracker Module Information\n"
		    "This program has no choice--it is doinkware\n"
		    "   [a.k.a. FreeWare, PD, do what ya want...]\n\n";

	char Protracker[]="ProTracker 1.1";

int main(int argc,char *argv[])
{
	FILE *fp;
	int outloop,loop,er;
	char temphi,templo;
	char modname[21];
	int RepStart, RepLen;
	char ModType[20];

	if (argc < 2)
	{
	fprintf(stderr,"%s",Use);
	return(5);
	}

	fprintf(stdout,"%s",Head);

	fp = fopen(argv[1],"rb");

	if (fp==NULL)
	  {
	  fprintf(stderr,"\nFile <%s> not found, or some other file error.",argv[1]);
	  return(5);
	  } /* endif */

	for(loop=0;loop<20;loop++)
	 {  modname[loop] = fgetc(fp); }
	 modname[20] = 0;

	for (outloop=0;outloop<31;outloop++)
	{
	  for(loop=0;loop<22;loop++)
	   {
	   Sample[outloop].Name[loop] = fgetc(fp);
	   }
	   temphi=fgetc(fp);templo=fgetc(fp);
	   Sample[outloop].Len=temphi*256+templo;
	   Sample[outloop].FineTune = fgetc(fp);
	   Sample[outloop].Vol = fgetc(fp);
	   temphi=fgetc(fp);templo=fgetc(fp);
	   Sample[outloop].RepStart = temphi*256+templo;
	   temphi=fgetc(fp);templo=fgetc(fp);
	   Sample[outloop].RepLen = temphi*256+templo;
	}
	SongLen = fgetc(fp);
	Dummy = fgetc(fp);
	for(outloop=0;outloop<128;outloop++)
	  {
	  SongPos[outloop] = fgetc(fp);
	  } /* end for */
	for(outloop=0;outloop<4;outloop++)
	  {
	  ModSig[outloop]=fgetc(fp);
	  } /* end for */
	  ModSig[4]=0;

	fclose(fp);

	if ( (ModSig[0]=='M')&&(ModSig[2]=='K') )
	 {
	 strcpy(ModType,Protracker);
	 }
	else
	 {
	 fprintf(stderr,"\n<%s> is not a protracker module.\n",argv[1]);
	 return(5);
	 }

	fprintf(stdout,"\nModule name  = \"%s\"\n",modname);
	fprintf(stdout,"Module Type  = %s\n",ModType);
	fprintf(stdout,"Song Length  = %d (%02x hex)\n",SongLen,SongLen);
	fprintf(stdout,"Pattern(s)   =");
	for (outloop=0;outloop<SongLen;outloop+=8)
	  {
	  for (loop=0;loop<8;loop++)
	   {
	   if ( (outloop+loop) < SongLen)
	   fprintf(stdout," %02x",SongPos[outloop+loop]);
	   }
	  fprintf(stdout,"\n              ");
	  }

	for (loop=0;loop<31;loop++)
	{
	  fprintf(stdout,"\nSample %d ",loop+1);
	  if (Sample[loop].Len==0)
	   { fprintf(stdout,"-- empty");
	     fprintf(stdout,"\nText   : \"%s\"\n",Sample[loop].Name);
	   } /* endif */
	  else
	   {
	   fprintf(stdout,"\nName   : \"%s\"\n",Sample[loop].Name);
	   fprintf(stdout,"Length : %d bytes (%04x hex)\n"
	    ,Sample[loop].Len, Sample[loop].Len);
	   fprintf(stdout,"Volume : %d (%02x hex)\n"
	    ,Sample[loop].Vol, Sample[loop].Vol);
	   RepStart = Sample[loop].RepStart;
	   RepLen   = Sample[loop].RepLen;

	   if (! ( (RepStart==0) && ((RepLen==1)||(RepLen==0)) ) )
	    {
	     fprintf(stdout,"Repeat Info\n");
	     fprintf(stdout,"Start  : %d (%04x hex)\n",RepStart,RepStart);
	     fprintf(stdout,"Length : %d (%04x hex)\n",RepLen  ,RepLen  );
	    } /* endif */
	  } /* end else */
	} /* end for (loop++) */

return(0);
} /* end main() */


