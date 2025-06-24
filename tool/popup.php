<?
include $_SERVER['DOCUMENT_ROOT'].'/inc/global.inc'; 

$sql = " Select * From df_site_content Where idx='".$idx."' ";
$popup_info = $db->row($sql);

if(!$popup_info['close_bg']) 		$popup_info['close_bg'] = "#cacaca";
if(!$popup_info['close_align']) 	$popup_info['close_align'] = "left";
if(!$popup_info['close_txt']) 		$popup_info['close_txt'] = "오늘 하루 열지 않음";
if(!$popup_info['close_txt_color'])	$popup_info['close_txt_color'] = "#000000";

if(!empty($popup_info['linkurl'])) {
	$urlstr = "onclick=\"javascript:opener.location = '".$popup_info['linkurl']."';window.close();\" style=\"cursor:hand;\"";
}
?>
<html>
<head>
<title><?=$popup_info['title']?></title>

<script language="javascript">
<!--
	function popupClose(){
		setCookie("popupDayClose<?=$idx?>", "true", 1);
		self.close();
	}

	function setCookie( name, value, expiredays ) { 
		var todayDate = new Date(); 
		todayDate.setDate( todayDate.getDate() + expiredays ); 
		document.cookie = name + "=" + escape( value ) + "; path=/; expires=" + todayDate.toGMTString() + ";" 
	} 
//-->
</script>

</head>
<body topmargin="0" leftmargin="0">

<table border="0" cellpadding="0" cellspacing="0">
	<tr>
		<td>
			<?=$popup_info['content']?>
		</td>
	</tr>
</table>

<table width="100%" height="25" border="0" align="right" cellpadding="0" cellspacing="0" bgcolor="<?=$popup_info['close_bg']?>" style="position:fixed; left:0; bottom:0;">
	<tr>
		<td align="<?=$popup_info['close_align']?>" style="padding-left:5px;">
			<span style="color:<?=$popup_info['close_txt_color']?>; font-size:12px; vertical-align:middle;"><?=$popup_info['close_txt']?></span>
			<input type="checkbox" onClick="popupClose<?=$pidx?>();" style="vertical-align:middle;">
		</td>
		<td align="right" style="width:30px; padding-right:5px;">
			<img src="/tool/images/x.gif" style="cursor:hand" onClick="self.close();" WIDTH="12" HEIGHT="11">
		</td>
	</tr>
</table>

</body>
</html>