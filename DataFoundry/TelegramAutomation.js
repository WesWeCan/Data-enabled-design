let ID = "PARTICIPANT DATA FOUNDRY ID"; // Found in resources page, use dev tools to copy the tooltip.

let hoursToRemind = [8, 20];
let message = "Hey! This is your reminder to reflect on your mood.";

// Generate a key for today
let key = "_" + data.y + "" + data.M + "" + data.d;

// Get the profile data entry from the database
let profile = DF.entity.get(ID);

// Check if there is already an entry in the database
if (profile[key] == undefined) {
    profile[key] = {};
    for(let i = 0; i < hoursToRemind.length; i++){
        profile[key][hoursToRemind[i]] = false;
    }
}

// Check if the current hour is in the hoursToRemind array
let index = hoursToRemind.indexOf(data.h); // Returns index or -1 on not found

if(index > -1){
    
    // Check if there is already send a reminder to the participant
    let isReminderAlreadySent = profile[key][hoursToRemind[index]];
    
    if(!isReminderAlreadySent){
      profile[key][hoursToRemind[index]] = true;
      
      DF.print("Sending Reminder")
      DF.telegramParticipant(ID, message)
    }
    else {
      DF.print("Reminder already sent")
    }
}
else {
  DF.print("No reminder in this hour.")
}

DF.entity.update(ID, profile);