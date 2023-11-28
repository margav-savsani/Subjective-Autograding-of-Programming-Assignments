import re

##########
#### SEARCH FOR TODO and fix


# Anything following "//" is a comment until end of line
commentPat = re.compile(r'//.*$')

# Grab anything within $...$. Make sure to use 
mathPat =  re.compile(r'\$(.*?)\$') 

#All id-like words, including optional leading '\' and 
# field access sequences 
# Examples: abc,  foo.length, \xxx
wordPat = re.compile(r'((\\){0,1}[a-zA-Z.]+)')

#Take a set of all the unique symbols in opsToTeX's keys. 
#Like this r'[<=>.]+'   etc. 
opPat = re.compile(r'([<=>.!-]+)')

# A line of the form "proc myfunc(a, b)".
procPat = re.compile(r'proc\s+([a-zA-Z-_]+\([a-zA-Z,\s]*\))')

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
    '<' : '<'            ,      '!=' : r'\neq'       ,      '=' : r'\eq'       ,  '-' : '-',
    '...' : r'\threedots',      '..' : r'\twodots'
}

def processLine(line):
    content = re.split(commentPat,line)[0]
    cmatch = re.search(commentPat,line)
    if cmatch == None :
        return processContent(content)
    comment = cmatch.group(0)
    return processContent(content) + processComment(comment[2:])
    # Split line into content part and comment part
    # Comments are always to the right, but are optional
    # return processContent(content) + processComment(comment)

def processContent(content):
    if not re.search(procPat,content) == None:
        return processProc(content)
    return '\zi' + processMath(content.replace('$','')) 
    # Treat the entire content as if it is already in math mode
    # processProc if it matches a proc line
    # Otherwise,
    # Treat the entire content as if it is already in math mode.
    # If there are any embedded '$...$' fragments, then strip the dollar signs
    # out.
    # Prepend '\zi' to the returned line, unless content matches a proc declaration

def processProc(lineMatch):    
    parts = re.split(r'(?:proc\s+|\(|\)\s*)',lineMatch)
    return '\Procname{\proc{' +parts[1]+ '}(' + processWords(parts[2])+')}'

def processMath(mathPart):
    return processWords(processOps(mathPart))
    # call processOps(processWords) on the matching part.

def processWords(fragment):
    return re.sub(wordPat, processWord, fragment)
    # call re.sub with wordPat and processWord

def processWord(wordMatch):
    word = wordMatch.group(0)
    if word[0] == '\\' :
        return word
    if '.' in word:
        attribs = word.split('.')
        return '\\attri' +'b'*(len(attribs)-1) + '{'+'}{'.join(attribs) + '}'
    if word in keywordsToTex:
        return keywordsToTex[word]
    return '\\id{'+word+'}'

    # Handle four cases. 
    #   Word starts with '\' ... return word untouched
    #   Word has embedded '.'. Convert "abc.def.ghi" to "\attribbb{abc}{def}{ghi}"
    #            The number of 'b's following attrib should equal the number of dots
    #   Word belongs to keywords (see testalgo.py for all keywords). Replace with latex substitute
    #   Otherwise replace with "\id{word}"

def processOps(fragment):
    if isinstance(fragment, re.Match):
        fragment = fragment.group(0)
    return re.sub(opPat , processOp, fragment)

def processOp(opMatch):
    op = opMatch.group(0)
    if op in opsToTeX.keys():
        return '$'+ opsToTeX[op] +'$'
    return op
    # replace op with matching latex equivalent if any, and surround with '$'
    # That is, '==' becomes '$\isequal$', but '===' remains unchanged.

def processComment(comment):
    return '\Comment '+re.sub(mathPat,processMath,comment)

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
    
   
