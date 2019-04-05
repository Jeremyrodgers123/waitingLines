#arrival rate, max Service Duration, random Seed

j = 0.5;
file = File.open("results.txt", "w")
file.print "x "
while j <= 5
    file.print "#{j} "
    j+= 0.5
end
file.print "\n"

11.times do |n|
    #puts n;
    file.print "#{n} "
    i = 0.5;
    while i <= 5
    #system("echo -n #{n} > results.txt")
        val = `./simulation #{i} #{n} 34534`
        file.print "#{val} "
#        puts "n: #{n} i: #{i} "
        puts val
        #system("echo '#{n} #{i} #{val}' >> results.txt")
        i += 0.5
    end
    file.print "\n"
    
end
