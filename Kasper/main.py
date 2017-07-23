from GhostEntity import GhostEntity

gh = GhostEntity()
line = '1350,1382,800,1638,1795,800,1596,1877,800,1290,1265,800'
gh.parsingLine(line)
print(gh.toDict())