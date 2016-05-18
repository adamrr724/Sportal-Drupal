<?php
/**
 * @file
 * Template for the weather module.
 */
?>
<div class="weather">
  <?php foreach($weather as $place): ?>
    <p style="clear:left"><strong><?php print $place['link']; ?></strong></p>
    <?php if (empty($place['forecasts'])): ?>
      <?php print(t('Currently, there is no weather information available.')); ?>
    <?php endif ?>
    <?php foreach($place['forecasts'] as $forecast): ?>
      <?php foreach($forecast['time_ranges'] as $time_range => $data): ?>
        <p style="clear:left">
          <?php print $forecast['formatted_date']; ?><br />
          <?php if (isset($forecast['sun_info'])): ?>
            <?php if (is_array($forecast['sun_info'])): ?>
              <?php print(t('Sunrise: @time', array('@time' => $forecast['sun_info']['sunrise']))); ?><br />
              <?php print(t('Sunset: @time', array('@time' => $forecast['sun_info']['sunset']))); ?><br />
            <?php else: ?>
              <?php print($forecast['sun_info']); ?><br />
            <?php endif ?>
          <?php endif ?>
          <?php print $time_range; ?>
        </p>
        <div style="float:left;margin-right:1em;margin-bottom:1em">
          <?php print $data['symbol']; ?>
        </div>
        <p style="font-size:125%">
          <?php print $data['condition']; ?><br />
          <?php print $data['temperature']; ?>
          <?php if (isset($data['windchill'])): ?>
            <br />
            <?php print(t('Feels like !temperature', array('!temperature' => $data['windchill']))); ?>
          <?php endif ?>
        </p>
      <?php endforeach; ?>
    <?php endforeach; ?>
    <?php if (isset($place['station'])): ?>
      <p style="clear:left">
        <?php print t('Location of this weather station:'); ?><br />
        <?php print $place['station']; ?>
      </p>
    <?php endif ?>
    <p style="clear:left">
      <?php print t('<a href="@url">Weather forecast from yr.no</a>, delivered by the Norwegian Meteorological Institute and the NRK',
        array('@url' => $place['yr.no'])); ?>
    </p>
  <?php endforeach; ?>
</div>
