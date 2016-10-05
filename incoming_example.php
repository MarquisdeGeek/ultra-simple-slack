<?php

require 'slack.inc';

$hookurl = 'YOUR_URL_GOES_HERE';

$slack = new SlackConduitOut($hookurl);

$msg = $slack->createMessage("We have successfully launched the USS Enterprise!");
$msg->setChannel("#announcements")->send();

?>