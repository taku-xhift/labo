
class Card
  def name
    puts "name card"
  end
end

class LabelCard < Card
  def name
    super
    puts "label card"
  end
  
  alias label name
end

card = LabelCard.new
card.name
card.label

