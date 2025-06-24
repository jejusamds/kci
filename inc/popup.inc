<?php
//==================================================================================================
//	MOBILE 팝업
//==================================================================================================
if ( $detect->isMobile() || $detect->isTablet() ){
	$today = date("Y-m-d");

	$sqlP = "";
	$sqlP .= "	Select	* ";
	$sqlP .= "	From	df_site_content_mobile ";
	$sqlP .= "	Where	type	= 'popup' ";
	$sqlP .= "	And		isuse	= 'Y' ";
	$sqlP .= "	And		sdate	<= '".$today."' ";
	$sqlP .= "	And		edate	>= '".$today."' ";
	$sqlP .= "	Order by	idx Desc ";
	$pop_row = $db->query($sqlP);

	if(count($pop_row) > 0){
?>
	<script type="text/javascript" language="javascript">
		$(document).ready(function(){
			// 팝업 쿠키체크
			if( getCookie("close_popup01")){
				$("#main_popup01").hide();
			}else{
				$("#main_popup01").show();
			}

			// 팝업 배경
			if($("#main_popup01").css("display")=="block"){
				$(".main_popup_con_bg").css("height", $(document).height()+"px").fadeIn("500");
			}

			// 이미지 리사이징
			$('.main_popup_con > .contents_con > .slide_con .swiper-container .swiper-wrapper .swiper-slide img').each(function(){
				$(this).css('max-width','100%');
				$(this).css('height','auto');
			});

			// 팝업 슬라이드
			var popup_slide = new Swiper ('.popup_slide', {
				autoHeight: true,
				slidesPerView: 'auto',
				effect: 'fade',
				autoplay: {
					delay: 3000,
				},
				speed: 1000,
				loop: true,
				pagination: {
					el: '.swiper-pagination',
					clickable: true,
				},
			});
		});
		
		function setCookie( name, value, expiredays ){
			var todayDate = new Date();
			todayDate.setDate( todayDate.getDate() + expiredays );
			document.cookie = name + "=" + escape( value ) + "; path=/; expires=" + todayDate.toGMTString() + ";"
		}
		
		function closeWin(idx){
			setCookie("close_"+idx,"close_"+idx,1);
			$("#main_"+idx).hide();
			$(".main_popup_con_bg").fadeOut("500");
		}
		
		function closeWinNo(idx){
			$("#main_"+idx).hide();
			$(".main_popup_con_bg").fadeOut("500");
		}
		
		function getCookie( cookieName ){
			var search = cookieName + "=";
			var cookie = document.cookie;
			
			if( cookie.length > 0 ){
				startIndex = cookie.indexOf( cookieName );
				if( startIndex != -1 ){
					startIndex += cookieName.length;
					endIndex = cookie.indexOf( ";", startIndex );
					if( endIndex == -1) endIndex = cookie.length;
					return unescape( cookie.substring( startIndex + 1, endIndex ) );
				}
				else{
					return false;
				}
			}
			else{
				return false;
			}
		}
	</script>

	<style>
		/*팝업*/
		.main_popup_con_bg {display:none; width:100%; margin:0 auto; background-color:#000000; background-color:rgba(0,0,0,0.6); position:fixed; top:0; left:0; right:0; z-index:400;}
		.main_popup_con {width:100%; margin:0 auto; position:fixed; top:10%; left:0; right:0; z-index:500;}
		.main_popup_con > .contents_con {margin:0 auto; position:absolute; top:0; left:0; right:0; z-index:10;}
		.main_popup_con > .contents_con > .slide_con {background-color:#f3f3f3; padding:5px;}
		.main_popup_con > .contents_con > .slide_con .swiper-container {width:100%; margin:0 auto;}
		.main_popup_con > .contents_con > .slide_con .swiper-container .slide_con-wrapper {}
		.main_popup_con > .contents_con > .slide_con .swiper-container-horizontal > .swiper-pagination-bullets {width:100%; margin:0 auto; bottom:10px; left:0; right:0; text-align:center;}
		.main_popup_con > .contents_con > .slide_con .swiper-container-horizontal > .swiper-pagination-bullets .swiper-pagination-bullet {width:10px; height:10px; background-color:#ac192f; margin:0 5px; border-radius:10px; opacity:0.5;}
		.main_popup_con > .contents_con > .slide_con .swiper-container-horizontal > .swiper-pagination-bullets .swiper-pagination-bullet-active {opacity:1;}
		.main_popup_con > .contents_con > .btn_con {}
		.main_popup_con > .contents_con > .btn_con > table {width:100%; margin:0 auto;}
		.main_popup_con > .contents_con > .btn_con > table > tbody > tr > td {width:30%;}
		.main_popup_con > .contents_con > .btn_con > table > tbody > tr > td label {display:block;}
		.main_popup_con > .contents_con > .btn_con > table > tbody > tr > td label > input {display:none;}
		.main_popup_con > .contents_con > .btn_con > table > tbody > tr > td label > span {display:block; background-color:#ac192f; text-align:center; font-size:12px; color:#ffffff; line-height:36px;}
		.main_popup_con > .contents_con > .btn_con > table > tbody > tr > td .a_btn {display:block; background-color:#7e7e7e; text-align:center; font-size:12px; color:#ffffff; line-height:36px;}
		.main_popup_con > .contents_con > .btn_con > table > tbody > tr > td:first-child {width:70%;}

		@media all and (max-width: 1024px) {
			.main_popup_con > .contents_con {width:86%;}
		}

		@media all and (max-width: 768px) {
			.main_popup_con > .contents_con {width:91.5%;}
		}
	</style>
	
	<div class="main_popup_con_bg"></div>
	<div class="main_popup_con" id="main_popup01">
		<div class="contents_con">
			<div class="slide_con">
				<div class="swiper-container popup_slide">
					<div class="swiper-wrapper">
						<? for($i=0; $i<count($pop_row); $i++){ ?>
						<div class="swiper-slide" data-swiper-autoplay="3000">
							<?=$pop_row[$i]['content']?>
						</div>
						<? } ?>
					</div>
					
					<div class="swiper-pagination"></div>
				</div>
			</div>

			<div class="btn_con">
				<table cellpadding="0" cellspacing="0">
					<tbody>
						<tr>
							<td align="left">
								<label>
									<input type="checkbox" name="notice" onClick="closeWin('popup01')" />
									<span>
										오늘 하루 동안 열지 않음
									</span>
								</label>
							</td>
							<td align="right">
								<a href="javascript:closeWinNo('popup01');" class="a_btn">
									창닫기
								</a>
							</td>
						</tr>
					</tbody>
				</table>
			</div>
		</div>
	</div>
<?
	}
}

//==================================================================================================
//	PC 팝업
//==================================================================================================
else{
?>
	<script language="javascript">
	<!--
		function readCookie(cookiename) {
			var Found = false;

			cookiedata = document.cookie; 
			if ( cookiedata.indexOf(cookiename) >= 0 ){ 
				Found = true;
			}

			return Found;
		}
	//-->
	</script>
<?php
	$today = date('Y-m-d');
	$sql = " Select * From df_site_content Where type='popup' And isuse='Y' And sdate<='".$today."' And edate>='".$today."' Order by idx Desc ";
	$popup_in = $db->query($sql);
	for($i=0; $i<count($popup_in); $i++){
		if($popup_in[$i]['poptype'] == "L") {
			$pidx = $popup_in[$i]['idx'];
			include $_SERVER['DOCUMENT_ROOT']."/tool/layerpop.php";
		}
		else {
			$popup_in[$i]['size_y'] = $popup_in[$i]['size_y'] + 27;
			echo "<script>";
			echo "if(!readCookie('popupDayClose".$popup_in[$i]['idx']."')){\n";
			echo "window.open('/tool/popup.php?idx=".$popup_in[$i]['idx']."','','height=".$popup_in[$i]['size_y'].", width=".$popup_in[$i]['size_x'].", menubar=no, scrollbars=".$popup_in[$i]['scroll'].", resizable=no, toolbar=no, status=no, top=".$popup_in[$i]['posi_y'].", left=".$popup_in[$i]['posi_x']."');\n";
			echo "}\n\n";
			echo "</script>";
		}
	}
}

?>
