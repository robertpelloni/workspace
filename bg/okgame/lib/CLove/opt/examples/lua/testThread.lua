
function load()
    local x = 0
    x = os.clock()
    local s = 0
    for i=1,10 do 
        s = s + i 
        os.execute("sleep "..1)
    end
    print(string.format("elapsed time: %.2f\n", os.clock() - x))
end
load()

