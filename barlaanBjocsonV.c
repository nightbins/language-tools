
/*********************************************************************************************************
This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
learned. I have constructed the functions and their respective algorithms and corresponding code by myself. The
program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole or
otherwise plagiarized the work of other students and/or persons.
 Bahir Benjamin C Barlaan, DLSU ID#12305987
 Vince Miguel S. Jocson, DLSU ID#12336149
 CCPROG2 S11
 *********************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX_ENTRY 150
#define MAX_PAIR 10

// initialization of structs
typedef char String30[31];
typedef char String20[21];
typedef char String150[151];

struct LanguagePair{
	String20 language;
	String20 translation;
};

typedef struct LanguagePair Pair;

struct entry{
	int entryindex;
	int paircount;
	Pair LanguageSet[10];
};

typedef struct entry Entry;

/* InitializeEntries initializes all entries to 0 or empty strings
   @param entrylist[] - array of entries to be initialized
   Pre-condition:
*/
void 
InitializeEntries(Entry entrylist[])
{
	int i, j;
	for(i = 0; i < MAX_ENTRY; i++)
	{
		entrylist[i].entryindex = 0;
		entrylist[i].paircount = 0;
		for(j = 0; j < MAX_PAIR; j++)
		{
			strcpy(entrylist[i].LanguageSet[j].language, "");
			strcpy(entrylist[i].LanguageSet[j].translation, "");
		}
	}
}

/* GetEntryCount returns the number entries in the list
   @param entrylist[] - Array of the Entry struct
   @return entryCount - the number of entries
   Pre-condition:
*/
int 
GetEntryCount(Entry entrylist[])
{
	int i; 
	int entryCount = 0;
	i = 0;
	while(entrylist[i].paircount != 0)
	{
		entryCount++;
		i++;
	}
	
	return entryCount;
}

/* Lowercase changes all characters in the string to lowercase
   @param *string - the string to be changed to lowercase
   Pre-condition:
*/
void 
Lowercase(char* string)
{
	int i;
	for(i = 0; i < strlen(string); i++)
	{
		if(string[i] <= 'Z' && string[i] >= 'A')
		{
			string[i] += 32;
		}
	}
}

/* GetLanguagePair gets the language pair from the user
   @param language - string where language will be stored
   @param translation - string where translation will be stored
   Pre-condition:
*/
void 
GetLanguagePair(String20 language, 
				String20 translation)
{
	printf("Enter Language: ");
	scanf(" %s", language);	
	Lowercase(language);
	language[0] -= 32;
	printf("Enter Translation: ");
	scanf(" %s", translation);
	Lowercase(translation);
	printf("\n");
}

/* DisplayEntry displays entry
   @param entrylist[] - list of entries
   @param param_index - index of chosen entry in the array
   Pre-condition: Entries exist in entrylist[]
*/
void 
DisplayEntry(Entry entrylist[], 
			int param_index)
{
	int i;
	printf("Entry #%d\n", entrylist[param_index].entryindex);
	printf("Language\t\tTranslation\t\t\n");
	for(i = 0; i < entrylist[param_index].paircount; i++)
	{
		printf("%d. %-10s\t\t", i+ 1, entrylist[param_index].LanguageSet[i].language);
		printf("%s\t\t\n", entrylist[param_index].LanguageSet[i].translation);
	}
	printf("\n");
}

/* SortEntry sorts the language pairs in an entry
   @param entrylist[] - list of entries
   @param param_index - index of the chosen entry
   Pre-condition: Entries exist in entrylist[]
*/
void 
SortEntry(Entry entrylist[], 
		int param_index)
{
	int i, j;
	int end = entrylist[param_index].paircount;
	int min = 0;
	String20 temp_language;	
	String20 temp_translation;
	
	for(i = 0; i < end; i++)
	{
		min = i;
		for(j = min + 1; j < end; j++)
		{
			if(strcmp(entrylist[param_index].LanguageSet[j].language, entrylist[param_index].LanguageSet[min].language) < 0)
			{
				min = j;
			}
		}
		if(min != j)
		{
			strcpy(temp_language, entrylist[param_index].LanguageSet[min].language);
			strcpy(entrylist[param_index].LanguageSet[min].language, entrylist[param_index].LanguageSet[i].language);
			strcpy(entrylist[param_index].LanguageSet[i].language, temp_language);
			strcpy(temp_translation, entrylist[param_index].LanguageSet[min].translation);
			strcpy(entrylist[param_index].LanguageSet[min].translation, entrylist[param_index].LanguageSet[i].translation);
			strcpy(entrylist[param_index].LanguageSet[i].translation, temp_translation);
		}
	}
}

/* DisplayAllEntries sorts and displays all entries with next, previous, and end display interface
   @param entrylist[] - list of entries
   Pre-condition:
*/
void 
DisplayAllEntries(Entry entrylist[])
{
	char cChoice;
	int i = 0;
	int end = 0;
	int valid;
	
	if(entrylist[i].paircount == 0)
		printf("No Entries Available.\n");
	while(entrylist[i].paircount != 0 && !end)
	{
		// sorts entries first before display
		SortEntry(entrylist, i);
		DisplayEntry(entrylist, i);
		do
		{
			if(entrylist[i + 1].paircount != 0)
				printf("N: Next\n");
			if(i != 0)
				printf("P: Previous\n");
			printf("X: End Display\n");
			printf("\n");
			printf("Enter choice: ");
			scanf(" %c", &cChoice);
			printf("\n");
			if(cChoice == 'N' || cChoice == 'n')
			{
				if(entrylist[i + 1].paircount != 0)
				{
					i++;
					valid = 1;
				}
				else
				{
					printf("No more entries left to show\n");
					valid = 0;
				}	
			}
			else if(cChoice == 'P' || cChoice == 'p')
			{
				if(i != 0)
				{
					i--;
					valid = 1;
				}
				else
				{
					printf("No previous entries\n");
					valid = 0;
				}	
			}
			else if(cChoice == 'X' || cChoice == 'x')
			{
				valid = 1;
				end = 1;
			}	
			else
			{
				valid = 0;
				printf("Invalid Response.\n");
			}
		} while(!valid);
	}
}

/* SearchTranslation searches and displays the entries found with the language and translation given
   @param entrylist[] - list of entries
   @param language
   @param translation
   @return 1 if entry is found
   @return 0 otherwise
   Pre-condition:
*/
int 
SearchTranslation(Entry entrylist[], 
				String20 language, 
				String20 translation)
{
	int i = 0;
	int j;
	int k = 0;
	int count = 0;
	Entry FoundEntries[MAX_ENTRY];	// where found entries are stored
	
	// initialize found entries array
	InitializeEntries(FoundEntries);
	
	while(entrylist[i].paircount != 0){	
		for(j = 0; j < entrylist[i].paircount; j++)
		{
			if(strcmp(entrylist[i].LanguageSet[j].language, language) == 0 &&
			strcmp(entrylist[i].LanguageSet[j].translation, translation) == 0)
			{
				//found entries are stored in FoundEntries[]
				FoundEntries[k] = entrylist[i];
				k++;
				count++;
			}
		}
		i++;
	}
	printf("\n");
	
	if(count > 0)
	{
		printf("Entries Found (%d):\n\n", count);
		DisplayAllEntries(FoundEntries);	//display all found entries
		return 1;
	}
	else
		return 0;
}

/* AddEntry adds an entry to the list
   @param entrylist[] - list of entries
   Pre-condition:
*/
void 
AddEntry(Entry entrylist[])
{
	int i;
	int j = 0;
	char choice;
	String20 language, translation;
	
	// ask for language pair
	GetLanguagePair(language, translation);
	
	// check entries if any entry matches pair and get index of last entry
	SearchTranslation(entrylist, language, translation);
	i = GetEntryCount(entrylist);
	
	// ask if it is a new entry
	printf("Is this a new entry? (y/n): ");
	scanf(" %c", &choice); 
	if(choice == 'y' || choice == 'Y')
	{
		j = 0;
		entrylist[i].paircount++;
		entrylist[i].entryindex = i + 1;
		strcpy(entrylist[i].LanguageSet[j].language, language);
		strcpy(entrylist[i].LanguageSet[j].translation, translation);
		j++;
		while((choice == 'y' || choice == 'Y') && entrylist[i].paircount < MAX_PAIR)
		{
			printf("Add more Language Pairs? (y/n): ");
			scanf(" %c", &choice);
			if(choice == 'y' || choice == 'Y')
			{
				GetLanguagePair(language, translation);
				entrylist[i].paircount++;
				strcpy(entrylist[i].LanguageSet[j].language, language);
				strcpy(entrylist[i].LanguageSet[j].translation, translation);
				j++;	
			}
		}
	}
}

/* AddTranslation adds a language pair to an entry
   @param entrylist[] - list of entries
   Pre-condition:
*/
void 
AddTranslation(Entry entrylist[])
{
	int i = 0;
	int j = 0;
	int count = 0;
	char choice;
	int index;
	int found_entry[MAX_ENTRY];
	int valid = 0;
	String20 language, translation;
	
	// ask for language pair
	GetLanguagePair(language, translation);
	
	// check entries if any entry matches pair
	while(entrylist[i].paircount != 0)
	{
		for(j = 0; j < entrylist[i].paircount; j++)
		{
			if(strcmp(entrylist[i].LanguageSet[j].language, language) == 0 &&
			strcmp(entrylist[i].LanguageSet[j].translation, translation) == 0)
			{
				found_entry[count] = i + 1;
				count++;
				printf("Entry Found: Entry %d\n", i + 1);
				DisplayEntry(entrylist, i);
			}
		}
		i++;
	}
	
	// determine if entry exists and add translations
	if(count == 0)
		printf("No such entry exists.\n");
	else
	{
		if(count > 1)
		{
			printf("Enter entry number to add translation: ");
			do
			{
				scanf(" %d", &index);
				i = 0;
				while(!valid && i < count)
				{
					if(found_entry[i] == index)
						valid = 1;
					i++;
				}
				if(!valid)
					printf("Invalid Entry!\n");
				if((index < 0 || index > 150) && valid)
				{
					printf("Invalid Value!\n");
					valid = 0;
				}
				else if(entrylist[index].paircount >= 10)
					printf("Entry already reached max translations.\n");
			} while(!valid);
			if(valid)
			{
				// adds language pair to the last index of the language pair array
				index--;
				GetLanguagePair(language, translation);
				entrylist[index].paircount++;
				j = entrylist[index].paircount - 1;
				strcpy(entrylist[index].LanguageSet[j].language, language);
				strcpy(entrylist[index].LanguageSet[j].translation, translation);
				j++;
				while((choice == 'y' || choice == 'Y') && entrylist[i].paircount < MAX_PAIR)
				{
					printf("Add more Language Pairs? (y/n): ");
					scanf(" %c", &choice);
					if(choice == 'y' || choice == 'Y')
					{
						GetLanguagePair(language, translation);
						entrylist[i].paircount++;
						strcpy(entrylist[index].LanguageSet[j].language, language);
						strcpy(entrylist[index].LanguageSet[j].translation, translation);
						j++;	
					}
				}
			}	
		}
		else // if there are no language pairs, add language pair to the first index
		{
			printf("Add new Language Pair? (y/n): ");
			scanf(" %c", &choice);
			if((choice == 'y' || choice == 'Y') && entrylist[found_entry[0] - 1].paircount < 10)
			{
				GetLanguagePair(language, translation);
				entrylist[found_entry[0] - 1].paircount++;
				j = entrylist[found_entry[0] - 1].paircount - 1;
				strcpy(entrylist[found_entry[0] - 1].LanguageSet[j].language, language);
				strcpy(entrylist[found_entry[0] - 1].LanguageSet[j].translation, translation);
				j++;
				do
				{
					printf("Add more Language Pairs? (y/n): ");
					scanf(" %c", &choice);
					if((choice == 'y' || choice == 'Y') && entrylist[found_entry[0] - 1].paircount < MAX_PAIR)
					{
						GetLanguagePair(language, translation);
						entrylist[found_entry[0] - 1].paircount++;
						strcpy(entrylist[found_entry[0] - 1].LanguageSet[j].language, language);
						strcpy(entrylist[found_entry[0] - 1].LanguageSet[j].translation, translation);
						j++;	
					}
				} while((choice == 'y' || choice == 'Y') && entrylist[found_entry[0] - 1].paircount < MAX_PAIR);
			}
		}
	}	
}

/* ModifyEntry lets user modify an entry
   @param entrylist[] - list of entries
   Pre-condition:
*/
void 
ModifyEntry(Entry entrylist[])
{
    int entryNumber, pairNumber;
    String20 language, translation;
    int done = 0;
    int entryCount = 0;
    int nChoice;
    char cChoice;
    Entry selectedEntry;
	
	//get number of total entries
	entryCount = GetEntryCount(entrylist);
	if(entryCount == 0)
		printf("No entries available.\n");
	else
	{
		// Display all entries
	    printf("Choose entry number after ending display.\n\n");
	    DisplayAllEntries(entrylist);
	
	    // Get entry number to modify
	    printf("Enter entry number to modify: ");
	    scanf("%d", &entryNumber);
	    printf("\n");
	
	    if(entryNumber < 1 || entryNumber > entryCount)
		{
	        printf("Invalid entry number.\n\n");
	        return;
	    }
	
	    selectedEntry = entrylist[entryNumber - 1];
	
	    while(!done)
		{
	        printf("Enter language-translation pair number to modify: ");
	        scanf("%d", &pairNumber);
	
	        if(pairNumber < 1 || pairNumber > selectedEntry.paircount)
			{
				printf("Invalid pair number.\n");
			} 
			else
			{
	            printf("1. Modify Language\n");
	            printf("2. Modify Translation\n");
	        	scanf("%d", &nChoice);
	        	printf("\n");
	            if (nChoice == 1)
				{
	                printf("Enter new language: ");
	                scanf(" %s", language);
	                Lowercase(language);
	                language[0] -= 32;
	            	strcpy(selectedEntry.LanguageSet[pairNumber - 1].language, language);
	            	printf("Language has been modified.\n\n");
	            }
				else if (nChoice == 2)
				{
	                printf("Enter new translation: ");
	                scanf(" %s", translation);
	                Lowercase(translation);
	                strcpy(selectedEntry.LanguageSet[pairNumber - 1].translation, translation);
	                printf("Translation has been modified.\n\n");
	            } 
				else
				{
	                printf("Invalid choice.\n\n");
	            }
	    	}
	    	printf("Modify another language-translation pair? (y/n): ");
	    	scanf(" %c", &cChoice);
	    	if(cChoice == 'N' || cChoice == 'n')
	    		done = 1;
	    	else if(cChoice == 'Y' || cChoice == 'y')
	    		done = 0;
	    	else
	    		printf("Invalid choice.\n");
	    }
	    entrylist[entryNumber - 1] = selectedEntry;
	}   
}

/* DeleteEntry lets user delete an entry
   @param entrylist[] - list of entries
   Pre-condition: 
*/
void
DeleteEntry(Entry entrylist[])
{
    int entryNumber;
    int entryCount = 0;
    int i;
    
    //get number of total entries
	entryCount = GetEntryCount(entrylist);
	
	if(entryCount == 0)
		printf("No entries available.\n");
	else
	{
		// Display all entries
	    printf("Choose entry number after ending display.\n\n");
	    DisplayAllEntries(entrylist);
	
	    // Get entry number to delete
	    printf("Enter entry number to delete: ");
	    scanf("%d", &entryNumber);
	    printf("\n");
	
	    if(entryNumber < 1 || entryNumber > entryCount)
		{
	        printf("Invalid entry number.\n\n");
	        return;
	    }
	
	    // Shift entries to the left to remove the entry
	    for(i = entryNumber - 1; i < entryCount; i++)
		{
	        entrylist[i] = entrylist[i + 1];
	        entrylist[i].entryindex--;
	    }
	    printf("Entry #%d has been deleted.\n", entryNumber);
	} 
}

/* DeleteTranslation lets user delete a language pair from an entry
   @param entrylist[] - list of entries
   Pre-condition: 
*/
void 
DeleteTranslation(Entry entrylist[])
{
    int entryNumber, pairNumber;
	int i;
	int entryCount = 0;
	Entry selectedEntry;
	
	//get number of total entries
	entryCount = GetEntryCount(entrylist);
	
	if(entryCount == 0)
		printf("No entries available.\n");
	else
	{
		// Display all entries
	    printf("Choose entry number after ending display.\n\n");
	    DisplayAllEntries(entrylist);
	
	    // Get entry number to delete translation from
	    printf("Enter entry number to delete translation from: ");
	    scanf("%d", &entryNumber);
	
	    if(entryNumber < 1 || entryNumber > entryCount)
		{
	        printf("Invalid entry number.\n");
	        return;
	    }
	
	    selectedEntry = entrylist[entryNumber - 1];
	
	    // Get language-translation pair number to delete
	    printf("Enter language-translation pair number to delete: ");
	    scanf("%d", &pairNumber);
	
	    if(pairNumber < 1 || pairNumber > selectedEntry.paircount)
		{
	        printf("Invalid pair number.\n");
	        return;
	    }
	
	    // Shift pairs to the left to remove the selected pair
	    for(i = pairNumber - 1; i < selectedEntry.paircount; i++)
	        selectedEntry.LanguageSet[i] = selectedEntry.LanguageSet[i + 1];
	
	    selectedEntry.paircount--;
		entrylist[entryNumber - 1] = selectedEntry;
		
	    // If the entry has no more pairs, remove the entry
	    if(selectedEntry.paircount == 0)
		{
	        for(i = entryNumber - 1; i < entryCount; i++) 
			{
	            entrylist[i] = entrylist[i + 1];
	            entrylist[i].entryindex--;
	        }
	    }
	    printf("Translation has been deleted.\n");	
	}
}

/* SearchWord searches for a word that matches any language pair in any entry
   @param entrylist[] - list of entries
   Pre-condition: Entries are loaded into the program
*/
void 
SearchWord(Entry entrylist[])
{
	int i = 0;
	int j = 0;
	int k = 0;
	int count = 0;
	int found;
	String20 keyword;
	Entry FoundEntries[MAX_ENTRY];
	
	// initialize found entries array
	InitializeEntries(FoundEntries);
	
	printf("Enter Search Keyword: ");
	scanf(" %s", keyword);
	Lowercase(keyword);
	
	// search keyword
	i = 0;
	while(entrylist[i].paircount != 0)
	{
		found = 0;
		j = 0;	
		while(!found && j < entrylist[i].paircount)
		{
			if(strcmp(entrylist[i].LanguageSet[j].translation, keyword) == 0)
			{
				//found entries are stored int FoundEntries.
				FoundEntries[k] = entrylist[i];
				k++;
				found = 1;
				count++;
			}
			else
				j++;
		}
		i++;
	}
	
	printf("\n");
	if(count > 0)
	{
		printf("Entries Found (%d):\n\n", count);
		DisplayAllEntries(FoundEntries);	//display all found entries
	}
	else
		printf("No Entries Found\n\n");
}

/* Export lets user save and export onto a text file
   @param entrylist[] - list of entries
   @param filename - name of the file to be exported
   Pre-condition:
*/
void 
Export(Entry entrylist[], 
		String30 filename)
{
	FILE *fp_exportfile;
	int entrycount = 0;
	int i, j;
	
	// get number of entries
	entrycount = GetEntryCount(entrylist);
	
	if(entrycount == 0)
		printf("No entries available.\n");
	else
	{
		strcat(filename, ".txt");	// append filename extension
		fp_exportfile = fopen(filename, "w");
		for(i = 0; i < entrycount; i++)
		{
			for(j = 0; j < entrylist[i].paircount; j++)
			{
				fprintf(fp_exportfile, "%s: ", entrylist[i].LanguageSet[j].language);
				fprintf(fp_exportfile, "%s\n", entrylist[i].LanguageSet[j].translation);
			}
			fprintf(fp_exportfile, "\n");	
		}
		fclose(fp_exportfile);
		printf("Entries saved in %s successfully.\n\n", filename);
	}
}

/* CompareImportEntry is used in Import to add entries in the list from the file after comparing to existing entries in the list.
   @param entrylist[] - list of entries
   @param importlist[] - list of entries obtained from Import
   Pre-condition:
*/
void 
CompareImportEntry(Entry entrylist[], 
					Entry importlist[])
{
	int e_i, e_j, lp_i;
	int i;
	int valid;
	char cChoice;
	int match = 0;
	int done = 0;
	int match_index;
	int match_entry;
	int importlist_count;
	int entrylist_count;
		
	// create temporary duplicates of both entrylist and import list
	Entry dEntryList[MAX_ENTRY];
	Entry dImportList[MAX_ENTRY];
	
	// initialize the duplicates
	InitializeEntries(dEntryList);
	InitializeEntries(dImportList);
	
	// copy values of lists to the duplicate lists
	entrylist_count = GetEntryCount(entrylist);
	for(i = 0; i < entrylist_count; i++)
		dEntryList[i] = entrylist[i];
		
	importlist_count = GetEntryCount(importlist);
	for(i = 0; i < importlist_count; i++)
		dImportList[i] = importlist[i];
	
	// sort temporary duplicates
	for(i = 0; i < entrylist_count; i++)
		SortEntry(dEntryList, i);
	for(i = 0; i < entrylist_count; i++)
		SortEntry(dImportList, i);
	
	// compare the lists
	e_i = 0;
	while(dImportList[e_i].paircount != 0)
	{
		e_j = 0;
		match_index = -1;
		match_entry = -1;
		done = 0;
		while(dEntryList[e_j].paircount != 0 && !done)
		{
			match = 0;
			if(dImportList[e_i].paircount == dEntryList[e_j].paircount)	// check if same number of language pairs
			{
				for(lp_i = 0; lp_i < dImportList[e_i].paircount; lp_i++)
				{
					// count number of matching language pairs
					if(strcmp(dImportList[e_i].LanguageSet[lp_i].language, dEntryList[e_j].LanguageSet[lp_i].language) == 0 &&
					strcmp(dImportList[e_i].LanguageSet[lp_i].translation, dEntryList[e_j].LanguageSet[lp_i].translation) == 0)
						match++;
				}
				// if all language pairs match, terminate inner loop
				if(match == dImportList[e_i].paircount)
				{
					match_index = e_i;
					match_entry = e_j;
					done = 1;	
				}
				else
					e_j++;
			}
			else
				e_j++;
		}
		// identical entry found, ask user if they will still import
		if(match_index != -1)
		{
			printf("Identical entry already found in database:\n");
			DisplayEntry(entrylist, match_entry);
			printf("Still import as new entry? (y/n): ");
			valid = 1;
			do
			{
				scanf(" %c", &cChoice);
				if(cChoice == 'Y' || cChoice == 'y')
				{
					// add importlist entry to entrylist
					entrylist_count = GetEntryCount(entrylist);
					entrylist[entrylist_count] = dImportList[match_index];
					entrylist[entrylist_count].entryindex = entrylist_count + 1;
					printf("Entry added.\n");
				}
				else if(cChoice == 'N' || cChoice == 'n')
					printf("Entry skipped.\n");
				else
				{
					printf("Invalid choice.\n");
					valid = 0;
				}
			} while(!valid);
		}
		// no identicals found, import
		else
		{
			entrylist_count = GetEntryCount(entrylist);
			entrylist[entrylist_count] = dImportList[e_i];
			entrylist[entrylist_count].entryindex = entrylist_count + 1;
		}
		e_i++;
	}
}

/* Import lets the user import entries from a text file
   @param entrylist[] - list of entries
   @param filename - filename of source file
   @return 1 if importing is successful
   @return 0 otherwise
   Pre-condition:
*/
int 
Import(Entry entrylist[], 
		String30 filename)
{
	FILE *fp_importfile;
	char ch[2];	// initialize ch as a string for strcat
	Entry temp_entry[MAX_ENTRY];
	int language;
	int newline;
	int i;
	int j;
	int entrylist_count;
	
	ch[1] = '\0'; //add null byte for ch
	
	//initialize the temp_entry
	InitializeEntries(temp_entry);
	
	strcat(filename, ".txt");
	if((fp_importfile = fopen(filename, "r")) == NULL)
	{
		printf("File %s does not exist.\n\n", filename);
		fclose(fp_importfile);
		return 0;
	}
	else
	{
		// read import file and store in temp_entry[]
		newline = 0;
		language = 1;
		i = 0;
		j = 0;
		temp_entry[i].entryindex = i + 1;
		while((fscanf(fp_importfile, "%c", ch)) == 1)
		{
			if(newline && ch[0] == '\n')
			{
				i++;
				j = 0;
				temp_entry[i].entryindex = i + 1;
			}
			newline = 0;
			if(ch[0] != ':' && language && ch[0] != '\n')
				strcat(temp_entry[i].LanguageSet[j].language, ch);
			else if(ch[0] == ':' || ch[0] == ' ')
				language = 0;
			else if(ch[0] != ':' && !language && ch[0] != '\n')
				strcat(temp_entry[i].LanguageSet[j].translation, ch);
			else if(ch[0] == '\n' && !language)
			{
				j++;
				language = 1;
				newline = 1;
				temp_entry[i].paircount++;
			}
		}
		//make entries lowercase
		for(i = 0; i < GetEntryCount(temp_entry); i++)
		{
			for(j = 0; j < temp_entry[i].paircount; j++)
			{
				Lowercase(temp_entry[i].LanguageSet[j].language);
				temp_entry[i].LanguageSet[j].language[0] -= 32;
				Lowercase(temp_entry[i].LanguageSet[j].translation);
			}
		}
		entrylist_count = GetEntryCount(entrylist);
		if(entrylist_count == 0)
		{
			i = 0;
			while(temp_entry[i].paircount != 0)
			{
				entrylist[i] = temp_entry[i];
				i++;
			}		
		}
		// if there are already existing entries in entrylist, call CompareImportEntry to compare before importing
		else
			CompareImportEntry(entrylist, temp_entry);
		fclose(fp_importfile);
		return 1;
	}
}

/* Tokenize splits a sentence into words stored in an array of strings
   @param sentence - sentence to tokenize
   @param Words[] - array of words to store the words in
   @param *pWordCount - pointer to update number of words in Words[]
   Pre-condition:
*/
void 
Tokenize(String150 sentence, String150 Words[], int *pWordCount){
	int i;
	int j = 0;
	
	*pWordCount = 0;
	strcat(sentence, " ");
	for(i = 0; i < strlen(sentence); i++){
		if(sentence[i] != ' ' && sentence[i] != '\0' && sentence[i] != ',' && sentence[i] != ';' &&
			sentence[i] != '?' && sentence[i] != '!' && sentence[i] != '.'){
			Words[*pWordCount][j] = sentence[i];
			j++;
		}
		else{
			Words[*pWordCount][j] = '\0';
			j = 0;
			(*pWordCount)++;
		}
	}
}

/* GetLanguages stores the languages from the database into an array
   @param entrylist[] - list of entries
   @param languages[] - array to store languages in
   @return languagecount - number of languages in the array of languages
   Pre-condition:
*/
int 
GetLanguages(Entry entrylist[], 
			String20 languages[])
{
	int i, j;
	int k = 0;
	int entrycount = GetEntryCount(entrylist);
	int languagecount;
	
	languagecount = 0;
	//copy all languages to array
	for(i = 0; i < entrycount; i++)
	{
		for(j = 0; j < entrylist[i].paircount; j++)
		{
			strcpy(languages[k], entrylist[i].LanguageSet[j].language);
			k++;
			languagecount++;
		}
	}
	
	// remove duplicates from array
	for(i = 0; i < languagecount; i++)
	{
		for(j = i + 1; j < languagecount; j++)
		{
			if((strcmp(languages[i], languages[j])) == 0)
			{
				for(k = j; k < languagecount - 1; k++)
				{
					strcpy(languages[k], languages[k + 1]);
				}
				languagecount--;
				j--;
			}
		}
	}

	return languagecount;
}

/* IdentifyMainLanguage identified the first and second most used language in a sentence or phrase
   @param entrylist[] - list of entries
   @param sentence - sentence to be identified
   Pre-condition:
*/
void 
IdentifyMainLanguage(Entry entrylist[], 
					String150 sentence)
{
	int i, j, k, m, n, d, add;
	int entrylist_count;
	int languagecount;
	String150 Words[MAX_ENTRY];
	int nWords;
	String20 Languages[MAX_ENTRY];
	int Tally[MAX_ENTRY];
	int max_index;
	int disable[MAX_ENTRY];
	
	// get number of entires
	entrylist_count = GetEntryCount(entrylist);
	
	// get languages available and the number of languages
	languagecount = GetLanguages(entrylist, Languages);
	
	// tokenize the sentence
	Tokenize(sentence, Words, &nWords);
	
	// initialize tally array to 0;
	for(i = 0; i < languagecount; i++){
		Tally[i] = 0;
	}
	
	for(i = 0; i < nWords; i++)
	{
		d = 0;	// initialize the array of disabled indices to -1
		for(n = 0; n < languagecount; n++){
			disable[n] = -1; 
		}
		for(j = 0; j < entrylist_count; j++)
		{
			for(k = 0; k < entrylist[j].paircount; k++)
			{
				if(strcmp(Words[i], entrylist[j].LanguageSet[k].translation) == 0)	// if word matches a translation in an entry
				{
					for(m = 0; m < languagecount; m++)
					{
						if(strcmp(Languages[m], entrylist[j].LanguageSet[k].language) == 0)
						{	// checks against all languages in array
							add = 1;
							// check first if a language of the same word was already checked earlier
							for(n = 0; n < languagecount; n++)
							{
								if(m == disable[n]) 
									add = 0;
							}
							if(add)
							{
								Tally[m]++;		
								disable[d] = m; // if language is ticked, disable this language until the word is done
								d++;
							}
						}
					}
				}
			}
		}
	}
	
	// gets the index of the maximum number in the tally
	max_index = 0;
	for(i = 1; i < languagecount; i++)
	{
		if(Tally[max_index] < Tally[i])
			max_index = i;
	}
	
	printf("Sentence:\n%s\n", sentence);
	if(Tally[max_index] != 0)
	{
		printf("The main language is %s.\n", Languages[max_index]);
		Tally[max_index] = 0;		// resets tally for the main language to zero to check for second main
		max_index = 0;
		for(i = 1; i < languagecount; i++)
		{	// finds the second main language index
			if(Tally[max_index] < Tally[i])
				max_index = i;
		}
		if(Tally[max_index] != 0)
		{
			printf("The second main language is %s.\n", Languages[max_index]);
		}
	}
	else
		printf("The main language is %s\n", "unknown");	
}

/* SimpleTranslation translates a sentence or phrase by checking each word in against the entries in the list
   @param entrylist[] - list of entries
   @param source_language - language of the provided sentence
   @param output_language - language of the translated sentence
   @param sentence - sentence to be translated
   @return 0 if translation fails
   @return 1 if translation proceeds
   Pre-condition:
*/
int
SimpleTranslation(Entry entrylist[], 
				String20 source_language, 
				String20 output_language, 
				String150 sentence)
{
	int i, j, k, m;
	int entrylist_count;
	int nWords;
	int source_found = 0;
	int output_found = 0;
	String150 Words[150];
	int translation_found;
	String150 translated_text;
	String20 Languages[MAX_ENTRY];
	int languagecount;
	
	// get languages
	languagecount = GetLanguages(entrylist, Languages);
	
	//check first if languages are in the entries
	for(i = 0; i < languagecount; i++)
		if(strcmp(source_language, Languages[i]) == 0)
			source_found = 1;	

	for(i = 0; i < languagecount; i++)
		if(strcmp(output_language, Languages[i]) == 0)
			output_found = 1;	
	
	if(output_found != 1 || output_found != 1){
		if(source_found != 1)
			printf("Source language not in database.\n\n");
		if(output_found != 1)
			printf("Output language not in database.\n");
		return 0;
	}
	else	// if output and source languages are found, proceed with function
	{
		// extract words from sentence
		Tokenize(sentence, Words, &nWords);
		
		// initializes the translated text
		strcpy(translated_text, "");
		
		// get number of entries
		entrylist_count = GetEntryCount(entrylist);
		for(i = 0; i < nWords; i++)
		{
			translation_found = 0;
			for(j = 0; j < entrylist_count; j++)
			{
				for(k = 0; k < entrylist[j].paircount; k++)
				{
					if(strcmp(source_language, entrylist[j].LanguageSet[k].language) == 0 &&	// find source language in entry list
					strcmp(Words[i], entrylist[j].LanguageSet[k].translation) == 0)				// find word in entry list
					{
						for(m = 0; m < entrylist[j].paircount; m++) 
						{
							if (strcmp(entrylist[j].LanguageSet[m].language, output_language) == 0) // find output language 
							{
	                            strcat(translated_text, entrylist[j].LanguageSet[m].translation);	// append output language translation
	                            strcat(translated_text, " ");	// append space for next word
	                            translation_found = 1;			// switches translation_found to true
	                            m = entrylist[j].paircount;
	                            k = entrylist[j].paircount;
	                            j = entrylist_count;			// terminates m, k, and j loop to stop searching in other entries or pairs.
	                        }
	                	}
					}
				}
			}
			if(!translation_found) 
			{
	            strcat(translated_text, Words[i]);	// if not found, append the original word
	            strcat(translated_text, " ");
	        }
		}
		printf("Sentence:\n%s\n", sentence);
		printf("Sentence translated in %s:\n", output_language);	
		printf("%s\n", translated_text);
		return 1;
	}	
}

int 
main()
{
	
	Entry EntryList[MAX_ENTRY];
	int nChoice;
	char cChoice;
	int back;
	int valid = 1;
	
	String20 language, translation, source_language, output_language;
	String30 filename;
	String150 sentence;
	String20 Languages[MAX_ENTRY];
	
	//initialize all entries
	InitializeEntries(EntryList);
	
	do
	{
		back = 0;
		printf("MAIN MENU:\n");
		printf("1. Manage Data\n");
		printf("2. Language Tools\n");
		printf("0. Exit\n");
		printf("\n");
		printf("Enter choice: ");
		scanf(" %d", &nChoice);
		printf("\n");
		if(nChoice == 1)
		{
			do
			{
				valid = 1;
				printf("MANAGE DATA MENU:\n");
				printf("1. Add Entry\n");
				printf("2. Add Translations\n");
				printf("3. Display All Entries\n");
				printf("4. Modify Entry\n");
				printf("5. Delete Entry\n");
				printf("6. Delete Translation\n");
				printf("7. Search Translation\n");
				printf("8. Search Word\n");
				printf("9. Export\n");
				printf("10. Import\n");
				printf("0. Exit\n");
				printf("\n");
				printf("Enter choice: ");
				scanf(" %d", &nChoice);
				printf("\n");
				switch(nChoice)
				{
					case 1:
					{
						AddEntry(EntryList);
						valid = 0;
						printf("\n");
						break;
					}
					case 2:
					{
						AddTranslation(EntryList);
						valid = 0;
						printf("\n");
						break;
					}
					case 3:
					{
						DisplayAllEntries(EntryList);
						printf("\n");
						valid = 0;
						break;
					}
					case 4:
					{
						ModifyEntry(EntryList);
						valid = 0;
						printf("\n");
						break;
					}
					case 5:
					{
						DeleteEntry(EntryList);
						valid = 0;
						printf("\n");
						break;
					}
					case 6:
					{
						DeleteTranslation(EntryList);
						valid = 0;
						printf("\n");
						break;
					}
					case 7:
					{
						GetLanguagePair(language, translation);
						if(SearchTranslation(EntryList, language, translation) == 0)
							printf("No entries found.\n");
						valid = 0;
						printf("\n");
						break;
					}
					case 8:
					{
						SearchWord(EntryList);
						valid = 0;
						printf("\n");
						break;
					}
					case 9:
					{
						printf("Enter export file filename: ");
						scanf(" %s", filename);
						printf("\n");
						Export(EntryList, filename);
						valid = 0;
						break;
					}
					case 10:
					{
						printf("Enter import file filename: ");
						scanf(" %s", filename);
						printf("\n");
						if(Import(EntryList, filename) == 1){
							printf("File is imported.\n\n");
						}
						valid = 0;
						break;
					}
					case 0:
					{
						InitializeEntries(EntryList);	// clear data in the lists
						back = 1;
						break;
					}
					default:
					{
						printf("Invalid Response.\n\n");
						valid = 0;
						break;
					}
				}
			} while(!valid);
		}
		else if(nChoice == 2)
		{
			printf("Enter filename of data file: ");
			scanf(" %s", filename);
			if(Import(EntryList, filename) == 1)
				printf("File is imported.\n\n");				
			else
				valid = 0;
			do
			{
				valid = 1;
				printf("LANGUAGE TOOLS MENU:\n");
				printf("1. Identify Main Language\n");
				printf("2. Simple Translation\n");
				printf("0. Exit\n");
				printf("\n");
				printf("Enter choice: ");
				scanf(" %d", &nChoice);
				printf("\n");
				switch(nChoice)
				{
					case 1:
					{
						GetLanguages(EntryList, Languages);
						printf("Enter phrase or sentence: ");
						scanf(" %[^\n]%*c", sentence);
						Lowercase(sentence);
						printf("\n");
						IdentifyMainLanguage(EntryList, sentence);
						printf("\n");
						valid = 0;
						break;
					}
					case 2:
					{
						printf("Enter source language: ");
						scanf(" %s", source_language);
						Lowercase(source_language);
						source_language[0] -= 32;
						printf("Enter phrase or sentence: ");
						scanf(" %[^\n]%*c", sentence);
						Lowercase(sentence);
						printf("Enter output language: ");
						scanf(" %s", output_language);
						Lowercase(output_language);
						output_language[0] -= 32;
						printf("\n");
						if(SimpleTranslation(EntryList, source_language, output_language, sentence) == 1)
						{
							printf("\n");
							do
							{
								printf("Translate another text in the same language? (y/n): ");
								scanf(" %c", &cChoice);
								if(cChoice == 'Y' || cChoice == 'y')
								{
									printf("Enter text to be translated: ");
									scanf(" %[^\n]%*c", sentence);
									Lowercase(sentence);
									printf("\n");
									SimpleTranslation(EntryList, source_language, output_language, sentence);
									valid = 0;
								}
								else if(cChoice == 'N' || cChoice == 'n')
								{
									printf("\n");
									valid = 1;
								}
								else
								{
									printf("Invalid response.\n");
									valid = 0;
								}
							} while(!valid);
						}
						else
							valid = 1;
						valid = 0;
						break;
					}
					case 0:
					{
						InitializeEntries(EntryList);
						back = 1;
						break;
					}
					default:
					{
						printf("Invalid Response.\n\n");
						valid = 0;
						break;
					}
				}
			} while(!valid);
		}
		else if(nChoice == 0)
			back = 0;
		else
			printf("Invalid Response.\n\n");
	} while(nChoice != 0 || back == 1);
	
	return 0;
}