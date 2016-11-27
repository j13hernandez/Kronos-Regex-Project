/**********************************************************************
 *  readme.txt template
 *  PS4b: Kronos log parsing
 **********************************************************************/

Name:   Daniel Santos


Hours to complete assignment (optional): 8


/**********************************************************************
 *  Did you complete the whole assignment?
 *  Successfully or not?
 *  Indicate which parts you think are working, and describe
 *    how you know that they're working.
 **********************************************************************/
Yes. Successfully.
I know they work beucase I compared them with your output.


/**********************************************************************
 *  Copy here all regex's you created for parsing the file,
 *  and explain individually what each ones does.
 **********************************************************************/
This find a match for the service start and group the name of the service
"Starting\\ Service\\.\\ \\ ([a-zA-z]+).+"

This find a match for the service completed and group the name of the service
and the time it took to complete
"Service\\ started\\ successfully\\.\\ \\ ([a-zA-Z]+).+\\(([0-9]+).+"


/**********************************************************************
 *  Describe your overall approach for solving the problem.
 *  100-200 words.
 **********************************************************************/
I first created the Boot class to hold of the information about a boot,
which was really fun doing because I made it that it prints itself with
the ostream operator<<. This makes the job of main easier. Then I created
Service class which, again, I made it that it print itself. So it works
like a chain. When you ask the a Boot object to print itself, it also
all the services inside the map. Which is pretty cool because when you
print one object, you are actually print several. Creating the regex was
not that bad because of the practice that we had from the other assignment.


/**********************************************************************
 *  List whatever help (if any) you received from lab TAs,
 *  classmates, or anyone else.
 **********************************************************************/
Non


/**********************************************************************
 *  Describe any serious problems you encountered.
 **********************************************************************/
Creating the classes and implementing the operator<<


/**********************************************************************
 *  List any other comments here.
 **********************************************************************/
