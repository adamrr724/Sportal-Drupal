<?php
/**
 * @file
 * Detailed template for the weather module.
 */
?>
<div class="weather">
  <?php foreach($weather as $place): ?>
    <p style="clear:left"><strong><?php print $place['name']; ?></strong></p>
    <?php if (empty($place['forecasts'])): ?>
      <?php print(t('Currently, there is no weather information available.')); ?>
    <?php endif ?>
    <?php foreach($place['forecasts'] as $forecast): ?>
      <p>
        <?php print $forecast['formatted_date']; ?>
        <?php if (isset($forecast['sun_info'])): ?>
          <br />
          <?php if (is_array($forecast['sun_info'])): ?>
            <?php print(t('Sunrise: @time', array('@time' => $forecast['sun_info']['sunrise']))); ?><br />
            <?php print(t('Sunset: @time', array('@time' => $forecast['sun_info']['sunset']))); ?>
          <?php else: ?>
            <?php print($forecast['sun_info']); ?>
          <?php endif ?>
        <?php endif ?>
      </p>
      <table>
        <thead>
          <th><?php print t('Time'); ?></th>
          <th><?php print t('Forecast'); ?></th>
          <th><?php print t('Temperature'); ?></th>
          <th><?php print t('Precipitation'); ?></th>
          <th><?php print t('Pressure'); ?></th>
          <th><?php print t('Wind'); ?></th>
        </thead>
        <?php foreach($forecast['time_ranges'] as $time_range => $data): ?>
          <tr>
            <td><?php print $time_range; ?></td>
            <td>
              <?php print $data['symbol']; ?>
              <?php print $data['condition']; ?>
            </td>
            <td>
              <?php print $data['temperature']; ?>
              <?php if (isset($data['windchill'])): ?>
                <br />
                <?php print(t('Feels like !temperature', array('!temperature' => $data['windchill']))); ?>
              <?php endif ?>
            </td>
            <td><?php print $data['precipitation']; ?></td>
            <td><?php print $data['pressure']; ?></td>
            <td><?php print $data['wind']; ?></td>
          </tr>
        <?php endforeach; ?>
      </table>
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
