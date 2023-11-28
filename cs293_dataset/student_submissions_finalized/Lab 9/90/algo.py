from concurrent.futures import process
import re
from time import CLOCK_THREAD_CPUTIME_ID

##########
#### SEARCH FOR TODO and fix


# Anything following "//" is a comment until end of line
commentPat = re.compile(r'//.*')

# Grab anything within $...$. Make sure to use 
mathPat =  re.compile( r'\$.*?\$' )

#All id-like words, including optional leading '\' and 
# field access sequences 
# Examples: abc,  foo.length, \xxx
wordPat = re.compile( r'\\*[A-Za-z][A-Za-z.]*' )

#Take a set of all the unique symbols in opsToTex's keys. 
#Like this r'[<=>.]+'   etc. 
opPat = re.compile( r'[<!=>+-.]+')

# A line of the form "proc myfunc(a, b)".
procPat = re.compile( r'^proc*.+' )

keywordsToTex = {
    'for'    : r'\For'        ,     'if'     : r'\If'          , 
    'end'    : r'\End'        ,     'then'   : r'\Then'        , 
    'while'  : r'\While'      ,     'do'     : r'\Do'          ,  
    'to'     : r'\To'         ,     'by'     : r'\By'          , 
    'downto' : r'\Downto'     ,     'repeat' : r'\Repeat'      , 
    'until'  : r'\Until'      ,     'elseif' : r'\Elseif'      ,
    'elsif'  : r'\Elseif'     ,     'return' : r'\Return'      , 
    'error'  : r'\Error'      ,     'nil'    : r'\const{nil}'  , 
    'true'   : r'\const{true}',     'false'  : r'\const{false}'
}

opsToTeX = {
    '<-' : r'\leftarrow' ,      '->' : r'\rightarrow',      '==' : r'\isequal' ,
    '<=' : r'\leq'       ,      '>=' : r'\geq'        ,      '>' : '>'          , 
    '<' : '<'            ,      '!=' : r'\neq'       ,      '=' : r'\eq'       , 
    '...' : r'\threedots',      '..' : r'\twodots'  ,       '-' : '-'       ,
    '+' : '+',
}

def processLine(line): ####################BUGGY
    parts = line.split("//")

    # if(commentPat.search(line)):
    #     return '\zi' + processComment(line)
    # else:
    #     # print('Hey There')
    #     return processContent(line)
    if(len(parts) != 2):
        return processContent(line)
    else:
        str1 = processContent(parts[0])
        str2 = processComment(parts[1])
        if(str1 and str2):
            return str1 + str2
        elif(str2):
            return str2
        else:
            return str1

    # TODO
    # Split line into content part and comment part
    # Comments are always to the right, but are optional
    # return processContent(content) + processComment(comment)

def processContent(content):
    # if re.match(procPat, content):
    #     processProc(re.match(procPat, content))
    if procPat.search(content):
        # print("Proc")
        return processProc(procPat.match(content))
    else:
        return "\zi" + processMath(content)

    # Treat the entire content as if it is already in math mode
    # processProc if it matches a proc line
    # Otherwise,
    # Treat the entire content as if it is already in math mode.
    # If there are any embedded '$...$' fragments, then strip the dollar signs
    # out.
    # Prepend '\zi' to the returned line, unless content matches a proc declaration

def processProc(lineMatch):
    # TODO
    # proc test-algo(A, B)
    # sample.algo firse badalna hain
    # \Procname{\proc{test-algo}(\id{A}, \id{B})}
   
   
    # line = lineMatch.group(0)
    # list = line.split(" ")
    # func = list[1]
    
    # str = r"\Procname{\proc{" + func + r"}("
    # for i in range(2,len(list)):
    #     param = list[i] ##############COULD BE REDUCED BY simply calling processWords for the parameter
    #     param = (((param.replace('(','')).replace(')','')).replace(' ','')).replace(',','')
    #     str+=r"\id{" + param + r"}, "
    # str = str[:-2]
    # str += ")}"
    # return str

    line = lineMatch.group(0)
    line = line.replace(','," ").replace('('," ").replace(')',"")
    list = re.split(" ",line)
    func = list[1]
    str = r"\Procname{\proc{" + func + r"}("
    for i in range(2,len(list)):
        if(list[i]!=""):
            str +=processWords(list[i])+", "
    str=str[:-2]+")}"
    return str


def processMath(mathPart):
    # TODO
    # mathMatch = re.match(opsToTeX, mathPart)
    # return processOps(processWords)
    # call processOps(processWords) on the matching part.
    return processOps(processWords(mathPart))

def processMaths(mathPart):
    # TODO
    # mathMatch = re.match(opsToTeX, mathPart)
    # return processOps(processWords)
    # call processOps(processWords) on the matching part.
    return processOps(processWords(mathPart.group(0)))[1:-1]

def processWords(fragment):
    return re.sub(wordPat, processWord, fragment)
    # call re.sub with wordPat and processWord

def processWord(wordMatch):
    word = wordMatch.group(0)
    if word == r'\\.*':
        return word
    parts = word.split('.')
    if len(parts) != 1:
        str = r"\attri"
        for i in range(0,len(parts)-1):
            str+="b"
        for i in parts:
            str+="{" + i + "}"
        return str
    if word in keywordsToTex:
        return keywordsToTex[word]
    return r"\id{" + word + "}" 
    
    # TODO
    # Handle four cases. 
    #   Word starts with '\' ... return word untouched
    #   Word has embedded '.'. Convert "abc.def.ghi" to "\attribbb{abc}{def}{ghi}"
    #            The number of 'b's following attrib should equal the number of dots
    #   Word belongs to keywords (see testalgo.py for all keywords). Replace with latex substitute
    #   Otherwise replace with "\id{word}"

def processOps(fragment):
    return re.sub(opPat, processOp, fragment)

def processOp(opMatch):
    op = opMatch.group(0)
    if op in opsToTeX:
        return '$' + opsToTeX[op] + '$'
    return op
    # TODO
    # replace op with matching latex equivalent if any, and surround with '$'
    # That is, '==' becomes '$\isequal$', but '===' remains unchanged.

def processComment(comment):

    # comment = comment.replace('//', r'\Comment')
    # MathMatch = mathPat.match(comment)
    # for i in MathMatch:
    #     i = processMath(i)

    # comment = comment.replace('$', '')
    return r"\Comment " + re.sub(mathPat, processMaths, comment)


    # TODO
    #Treat comment as if it is in text mode, but all embedded math expressions must be translated
    #by processMath
    # See testalgo.py for expected behaviur

def main(filename):
    with open(filename) as f:
        print(r'\begin{codebox}')
        for line in f:
            line = line.rstrip()
            print(processLine(line))
        print(r'\end{codebox}')

def usage():
    print("""
algo.py <file.algo>
Translates a pseudocode algorithm to LaTeX's clrscode3e environment. 
The format is a simplification of that environment, the objective being to 
not have to introduce math-mode or have special keywords like \For and \If 

Keywords: 
- Loops: for, to, by, downto, do, while, repeat, until
- Selection: if, then, else, elseif/elsif
- Jumps: return, error, goto
- Constants: nil, true, false

do/end blocks are required for indent/dedent, but do not appear in final output

Operators like <-, !=, ==, <= etc are replaced by the LaTeX equivalents.

Example:

proc insertion-sort(A, B)
   for j <- 2 to A.length do
      key <- A[j] // Insert $A[j]$ into the sorted sequence $A[1 .. j-1]$
      i <- j - 1
      while i > 0 and A[i] > key do
         A[i+1] <- A[i]
         i <- i - 1
      end
      A[i+1] <- key
   end
   if x == 3 then do
      {{Do something special}}
   end
end

""")

if __name__ == "__main__":
    import sys

    if len(sys.argv) != 2:
        usage()
        sys.exit(1)

    main(sys.argv[1])
    
   
